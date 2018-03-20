/************************************************************************
****	> File Name:    	getFileClusters_FAT32.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月19日 星期一 22时34分03秒
************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

typedef unsigned long address_type;
typedef int number_type;

//bpb
static number_type bytes_per_sector; //reserved
static number_type sectors_per_cluster;
static number_type fat_count;
static number_type root_begin_cluster;
static number_type reserved_sector_count;
static number_type sectors_per_fat;

//fat32 args
static address_type twoth_cluster_begin_address;
static address_type root_dir_begin_address;
static address_type fat1_begin_address;

static number_type bytes_per_cluster;

//buffer size of one cluster, init by open_device function
static char *buf;

#define BYTES_PER_DIR_ENTRY 0x20
#define BYTES_PER_SECTORS 0x200
#define get_address_by_cluster_number(x) \
        ((x-2) * bytes_per_cluster + twoth_cluster_begin_address)

bool open_device_readOnly(const string &device_name,int &fd) {
    fd = open(device_name.c_str(), O_RDONLY);
    if (fd < 0) return false;

    buf = new char[BYTES_PER_SECTORS];
    return true;
}

bool init_bpb(int &fd)
{
    int stat = lseek(fd, 0, SEEK_SET);
    if (stat == -1) return false;

    ssize_t read_number = read(fd, buf, BYTES_PER_SECTORS);
    if (read_number != BYTES_PER_SECTORS) {
        return false;
    }

    //judge whether FAT32
    char FAT32[] = "FAT32";
    for (int i=0; i<5; ++i) {
        if (buf[0x52+i] != FAT32[i]) {
            return false;
        }
    }

    //init
    bytes_per_sector = *(unsigned short*)&buf[0x0B];
    sectors_per_cluster = *(unsigned char*)&buf[0x0D];
    reserved_sector_count = *(unsigned short *)&buf[0x0E];
    fat_count = *(unsigned char *)&buf[0x10];
    sectors_per_fat = *(unsigned int *)&buf[0x24];
    root_begin_cluster = *(unsigned int *)&buf[0x2C];

    //change buf from one sector size to one cluster size
    delete [] buf;
    buf = new char[sectors_per_cluster * BYTES_PER_SECTORS];

    return true;
}


void get_fat_args()
{
    fat1_begin_address = reserved_sector_count * BYTES_PER_SECTORS;

    twoth_cluster_begin_address = fat1_begin_address
        + fat_count * sectors_per_fat * BYTES_PER_SECTORS;

    root_dir_begin_address = 
                (root_begin_cluster - 2) * sectors_per_cluster * BYTES_PER_SECTORS
                + twoth_cluster_begin_address;

    bytes_per_cluster = sectors_per_cluster * BYTES_PER_SECTORS;
}

void show_bpb_args() {
    cout << "sectors_per_cluster is \t\t" << sectors_per_cluster << "\n";
    cout << "fat_count is \t\t\t" << fat_count << "\n";
    cout << "root_begin_cluster is \t\t" << root_begin_cluster << "\n";
    cout << "reserved_sector_count is \t" << reserved_sector_count << "\n";
    cout << "sectors_per_fat is \t\t" << sectors_per_cluster << "\n" << endl;
}
void show_fat_args() {
    cout << showbase << hex;
    cout << "fat1_begin_address is \t\t" << fat1_begin_address << "\n";
    cout << "twoth_cluster_begin_address is \t" << twoth_cluster_begin_address << "\n";
    cout << "root_dir_begin_address is \t" << root_dir_begin_address << "\n";
    cout << noshowbase << dec << endl;
}
 
bool read_one_cluster_at(address_type address, int fd) {

    lseek(fd, address, SEEK_SET);
    if (read(fd, buf, bytes_per_cluster) != (long)bytes_per_cluster) {
        return false;
    }
    return true;
}

void get_clusterList_by_firstClusterNumber(number_type cluster_number, 
                                    vector<number_type> &cluster_list, int &fd) 
{
    cluster_list.erase(cluster_list.begin(), cluster_list.end());
    //not check the cluster 

    while (cluster_number != 0x0FFFFFFF) {
        cluster_list.push_back(cluster_number);
        address_type cluster_number_address = fat1_begin_address + cluster_number * 4;
        lseek(fd, cluster_number_address, SEEK_SET);
        if(read(fd, &cluster_number, 4) != 4) {
            cout << "fetal error!" << endl;
            exit(-1);
        }
    }
}

void extend_file_name(const char *src, char *des)
{ 
    int des_size = strlen(src);
    des[11] = '\0';
    int add_zero_number = 11 - des_size;
    int loc = 0;
    int argv1_loc = 0;
    for (; loc<11&&argv1_loc<des_size;) {
        if (src[argv1_loc] != '.') {
            if (src[argv1_loc] >= 'a' && src[argv1_loc] <= 'z')
                des[loc] = src[argv1_loc] - 'a' + 'A';
            else {
                des[loc] = src[argv1_loc];
            }
        } else {
            int k=0;
            for (; k<add_zero_number; ++k) {
                des[loc] = 0x20;
                ++loc;
            }
            des[loc] = 0x20;
        }
        ++loc;
        ++argv1_loc;
    }
    while (loc<11) {
        des[loc] = 0x20;
        ++loc;
    }
}
//use this func, make sure filename is WIN32 legally char and short name format
number_type get_fileFirstClusterNumber_by_fatherClusterList_and_filename(
        const vector<number_type> &cluster_list,
        const char *filename,
        int &fd)
{
    char extend_filename[12];
    extend_filename[11] = 0;
    extend_file_name(filename, extend_filename);
    /*cout << extend_filename << endl;*/

    int cluster_list_size = cluster_list.size();
    for (int i=0; i<cluster_list_size; ++i) {
        /*
         *cout << hex;
         *cout << get_address_by_cluster_number(cluster_list[i]) << endl;
         *cout << dec;
         */
        read_one_cluster_at(get_address_by_cluster_number(cluster_list[i]), fd);
        for (int j=0; j<int(bytes_per_cluster / BYTES_PER_DIR_ENTRY); ++j) {
            int flag = true;
            /*
             *cout << "extend_filename is \t";
             *for (int k=0; k<11; ++k) {
             *    cout << extend_filename[k];
             *}
             *cout << endl;
             *cout << "buf_there is \t\t";
             *for (int k=0; k<11; ++k) {
             *    cout << buf[j*BYTES_PER_SECTORS + k]; 
             *}
             *cout << "\n" << endl;
             */
            for (int k=0; k<11; ++k) {
                if (extend_filename[k] != buf[j*BYTES_PER_DIR_ENTRY + k]) {
                    flag = false; break;
                }
            }
            if (flag) {
                unsigned short cluster_number_high = 
                    *(unsigned short *)&buf[j*BYTES_PER_DIR_ENTRY + 0x14];
                unsigned short cluster_number_low = 
                    *(unsigned short *)&buf[j*BYTES_PER_DIR_ENTRY + 0x1A];
                return ((cluster_number_high << 16) + cluster_number_low);
            }
        }
    }

    return -1;
}

void filename_split(const string &absolute_filename, vector<string> &filenames) {
    string temp_str = "";
    for (auto i=absolute_filename.begin(); i!=absolute_filename.end(); ++i) {
        if (*i == '/') {
            filenames.push_back(temp_str);
            temp_str = "";
            continue;
        }
        temp_str += *i;
    }
    filenames.push_back(temp_str);

    //filenames check!
}


void getFileCluster_FAT32(const string &absolute_filename, const string &device)
{
    //init
    int fd;
    if (!open_device_readOnly(device, fd)) {
        cout << "open device error, maybe you don't have the privilege!" << endl;
        exit(0);
    }
    if (!init_bpb(fd)) {
        cout << "init_bpb error!" << endl;
        exit(0);
    }
    get_fat_args();

    //get filenames 
    vector<string> filenames;
    filename_split(absolute_filename, filenames);

    //search cluster list
    vector<number_type> father_cluster_list;
    father_cluster_list.push_back(root_begin_cluster); // init cluster list only have root_dir cluster 
    
    cout << "\tI'll find the '" << absolute_filename << "' file's cluster list" << "\n";
    cout << "result show below:" << "\n";
    cout << "first we at root_begin_cluster which is " << root_begin_cluster << endl;
    cout << "*********************************************************" << endl;
    for (auto i=filenames.begin(); i!=filenames.end(); ++i) {
        if (*i == "") continue;
        cout << "then I'll find the '" << *i << "'" << endl;
        number_type cur_file_first_cluster;   
        if ( (cur_file_first_cluster = 
                    get_fileFirstClusterNumber_by_fatherClusterList_and_filename(father_cluster_list,
                        i->c_str(), fd)) == -1) {
            cout << "sorry, there is no '" << *i << "' at file '" << *(i-1) << "'" << endl;
            exit(0);
        }
        get_clusterList_by_firstClusterNumber(cur_file_first_cluster, father_cluster_list, fd);
        cout << "\tI find the '" << *i << "' cluster list is ";
        for (const auto &a : father_cluster_list) cout << a << " -> ";
        cout << "end\n"; 
        cout << "*********************************************************" << endl;
    }
}

int main(int args, char **argv)
{
    if (args != 5) {
        cout << "Usage: elf -d device -f filename" << endl;
        return 0;
    }

    string device = argv[2];
    string filename = argv[4];
    
    getFileCluster_FAT32(filename, device);

    return 0;
}
/*
 *int main()
 *{
 *    string device_name = "/dev/sdc1";
 *    int fd;
 *    if(!open_device_readOnly(device_name, fd)) {
 *        cout << "open device error!" << endl;
 *        return 0;
 *    }
 *    if (!init_bpb(fd)) {
 *        cout << "init_bpb error!" << endl;
 *        return 0;
 *    }
 *    get_fat_args();
 *    show_bpb_args();
 *    show_fat_args();
 *
 *    return 0;
 *}
 */
