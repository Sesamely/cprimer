/************************************************************************
****	> File Name:    	getFileCluster_NTFS.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月21日 星期三 15时25分22秒
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

#define BYTES_PER_SECTOR 0x200
#define BYTES_PER_FILE_RECORD 0x400
#define ROOT_MTF_NUMBER 5

int fd; // global file descripter
unsigned char *buf;

//bpb args
typedef long int number_type;
typedef long int address_type;
number_type sectors_per_cluster; //一簇的扇区数
number_type MFT_begin_cluster_number;
number_type bytes_per_cluster;
address_type MFT_begin_adress;

void disp_this_func_global_var()
{
    cout << "sectors_per_cluster is \t" << sectors_per_cluster << "\n";
    cout << "MFT_begin_adress is \t" << MFT_begin_adress << "\n";
    cout << endl;
}

bool init_bpb()
{
    lseek(fd, 0, SEEK_SET);
    if (read(fd, buf, BYTES_PER_SECTOR) != BYTES_PER_SECTOR) {
        cerr << "\nread DBR error\n" << endl;
        return false;
    }
    string NTFS = "NTFS";
    for (int i=0; i<4; ++i) {
        if (buf[0x3+i] != NTFS[i])  {
            cerr << "\nthis is not a NTFS partition\n" << endl;
            return false;
        }
    }
    sectors_per_cluster = (unsigned char)buf[0xD];
    MFT_begin_cluster_number = *(unsigned long *)&buf[0x30];
    bytes_per_cluster = sectors_per_cluster * BYTES_PER_SECTOR;
    MFT_begin_adress = MFT_begin_cluster_number * bytes_per_cluster;

    delete [] buf;
    buf = new unsigned char[bytes_per_cluster];
    return true;
}


inline bool read_file_record_by_MFT_number(number_type cur_file_mft_num)
{
    lseek(fd, MFT_begin_adress + cur_file_mft_num*BYTES_PER_FILE_RECORD, SEEK_SET);
    if (read(fd, buf, BYTES_PER_FILE_RECORD) != BYTES_PER_FILE_RECORD) {
        cerr << "\tread file record error!" << endl;
        return false;
    }
    return true;
}

inline bool open_device_READONLY(const string &device)
{
    if ( (fd = open(device.c_str(), O_RDONLY)) < 0) {
        cerr << "\topen '" << device << "' error" << endl;
        return 0;
    }
 
    buf = new unsigned char[BYTES_PER_SECTOR];
    return true;
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

bool get_file_data_clusters(number_type file_MFT_number,
                            vector<number_type> &data_clusters)
{
    if (file_MFT_number == -1) return false;

    data_clusters.erase(data_clusters.begin(), data_clusters.end());

    if(!read_file_record_by_MFT_number(file_MFT_number)) {
        cerr << "\tfunc read_file_record_by_MFT_number error" << endl;
        exit(-1);
    }

    address_type offset = *(unsigned short *)&buf[0x14];
    while (offset<BYTES_PER_FILE_RECORD &&
          *(unsigned int *)&buf[offset] != 0x80 &&
          *(unsigned int *)&buf[offset] != 0xFFFFFFFF)
    {
        offset = offset + *(unsigned short *)&buf[offset + 0x4];
        /*cout << "offset is \t" << offset << endl;*/
    }
    if (*(unsigned int *)&buf[offset] == 0x80) {
        if (buf[offset + 0x08]) {
            //非常驻属性
            //以下offset 为 run list 的开始offset
            offset += *(unsigned short *)&buf[offset + 0x20];

            while (buf[offset] != 0x00) {
                int begin_cluster_length = (buf[offset] & 0xF0) >> 4;
                int clusters_length = buf[offset] & 0x0F;
                if (begin_cluster_length > 8 || clusters_length > 8) {
                    cerr << "\tmaybe run list infomation error?" << endl;
                    exit(-1);
                }
                long clusters_num=0, begin_cluster_num=0;
                for (int i=clusters_length-1; i>=0; --i) {
                    clusters_num <<= 8;
                    clusters_num += buf[offset + 1 + i];
                }
                /*cout << "cluster_num is \t" << clusters_num << endl;*/
                for (int i=begin_cluster_length-1; i>=0; --i) {
                    begin_cluster_num <<= 8;
                    begin_cluster_num += buf[offset + 1 + clusters_length + i];
                }
                /*cout << "begin_cluster_num is \t" << begin_cluster_num << endl;*/
                for (int i=0; i<clusters_num; ++i) {
                    data_clusters.push_back(begin_cluster_num++);
                } 
                offset += (begin_cluster_length + clusters_length + 1);
            }
        } else {
            //常驻属性
            
        }
        return true;
    }
    return false;
}

//uncompleted !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool get_file_index_clusters(number_type file_MFT_number,
                            vector<number_type> &index_clusters)
{
    if (file_MFT_number == -1) return false;

    index_clusters.erase(index_clusters.begin(), index_clusters.end());
    if(!read_file_record_by_MFT_number(file_MFT_number)) {
        cerr << "\tfunc read_file_record_by_MFT_number error" << endl;
        exit(-1);
    }
    address_type offset = *(unsigned short *)&buf[0x14];
    while (offset<BYTES_PER_FILE_RECORD &&
          *(unsigned int *)&buf[offset] != 0x90 &&
          *(unsigned int *)&buf[offset] != 0xFFFFFFFF)
    {
        /*cout << hex << showbase << offset << noshowbase << dec << endl;*/
        offset = offset + *(unsigned short *)&buf[offset + 0x4];
    }
    if (*(unsigned int *)&buf[offset] == 0x90) {
        address_type attr_content_offset;
        attr_content_offset = *(unsigned short *)&buf[offset + 0x14] + offset;
        // do something
        offset += *(unsigned int *)&buf[offset + 0x4];
    }
    if (*(unsigned int *)&buf[offset] == 0xA0) {
        //A0属性一定是非常驻属性
        
            /*address_type max_offset = offset + *(unsigned int *)&buf[offset+0x4];*/
            offset += *(unsigned short *)&buf[offset + 0x20];

            while (buf[offset] != 0x00) {
                int begin_cluster_length = (buf[offset] & 0xF0) >> 4;
                int clusters_length = buf[offset] & 0x0F;

                if (begin_cluster_length > 8 || clusters_length > 8) {
                    cerr << "\tmaybe run list infomation error?" << endl;
                    exit(-1);
                }
                long clusters_num=0, begin_cluster_num=0;
                for (int i=clusters_length-1; i>=0; --i) {
                    clusters_num <<= 8;
                    clusters_num += buf[offset + 1 + i];
                }
                /*cout << "cluster_num is \t" << clusters_num << endl;*/
                for (int i=begin_cluster_length-1; i>=0; --i) {
                    begin_cluster_num <<= 8;
                    begin_cluster_num += buf[offset + 1 + clusters_length + i];
                }
                /*cout << "begin_cluster_num is \t" << begin_cluster_num << endl;*/
                for (int i=0; i<clusters_num; ++i) {
                    index_clusters.push_back(begin_cluster_num++);
                } 
                /*
                 *cout << "\noffset is \t" << offset << endl;
                 *cout << "begin_cluster_length is \t" << begin_cluster_length << endl;
                 *cout << "clusters_length is \t" << clusters_length << endl;
                 */
                offset += (begin_cluster_length + clusters_length + 1);
                /*cout << "offset is \t" << offset << "\n" << endl;*/
            }

        return true;
    }

    return false;
}

inline bool read_one_cluster_at(number_type cluster_number) {
    lseek(fd, cluster_number * bytes_per_cluster, SEEK_SET);
    if (read(fd, buf, bytes_per_cluster) != bytes_per_cluster) {
        cerr << "\tread cluster at '" << cluster_number << "' error!" << endl;
        return false;
    }
    return true;
}

//not correct
number_type get_file_MFT_number_by_filename_and_indexClusters(const string &filename,
                                    const vector<number_type> &index_clusters)
{
    int filename_length = filename.size();
    char extend_filename[filename_length*2];
    for (int i=0; i<filename_length; ++i) {
        extend_filename[2*i] = filename[i];
        extend_filename[2*i + 1] = 0x00;
    }
    /*
     *cout << "extend_filename is \t";
     *for (int i=0; i<filename_length*2; ++i) {
     *    if (extend_filename[i] == 0x00) cout << "*";
     *    else cout << extend_filename[i];
     *}
     *cout << endl;
     */

    int index_clusters_cnt = index_clusters.size();

/********************************************************************************************/
    if (index_clusters_cnt > 1) index_clusters_cnt = 1; // only support one index cluster
/********************************************************************************************/

    for (int i=0; i<index_clusters_cnt; ++i) {
        if (!read_one_cluster_at(index_clusters[i])) {
            exit(-1);
        }
        address_type offset = *(unsigned short *)&buf[0x18] + 0x18;
        while (offset < bytes_per_cluster &&
              *(unsigned long *)&buf[offset] != 0) 
        {
            /*cout << "\noffset is \t" << hex << offset << dec << "\n" << endl;*/
            if (buf[offset + 0x50] == filename_length) {
                int flag = true;
                for (int i=0; i<filename_length*2; ++i) {
                    if (extend_filename[i] != buf[offset + 0x52 +i]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    /*
                     *cout << "\tget file MFT number by filename return is \t" << 
                     *    (*(unsigned long *)&buf[offset]& 0x0000FFFFFFFFFFFF) << "\n" << endl;
                     */
                    return ((*(unsigned long *)&buf[offset]) & 0x0000FFFFFFFFFFFF);
                }
            }
            offset += *(unsigned short *)&buf[offset + 0x08];
        }
    }
    
    return -1;
}

void getFileClusters_NTFS(const string &complete_filename, 
                          const string &device)
{
    if (!open_device_READONLY(device)) {
        exit(-1);
    }
    if (!init_bpb()) {
        exit(-1);
    }

    vector<string> filenames;
    filename_split(complete_filename, filenames);
    int filenames_size = filenames.size();

    vector<number_type> file_index_clusters;
    get_file_index_clusters(ROOT_MTF_NUMBER, file_index_clusters); //get root index clusters
    /*for (const auto &a : file_index_clusters) cout << a << " "; cout << endl;*/

    int i;
    for (i=0; i<filenames_size-1; ++i) {

        if (filenames[i] == "") continue;

        if (!get_file_index_clusters(
            get_file_MFT_number_by_filename_and_indexClusters(filenames[i], file_index_clusters),
            file_index_clusters)) {
                cerr << "\terror when get_file_index_cluster" << endl;
                exit(-1);
            }
    }

    /*cout << "\ntest1\n" << endl;*/
    number_type file_MFT_number = 
        get_file_MFT_number_by_filename_and_indexClusters(filenames[i], file_index_clusters);

    /*cout << "\ntest2\n" << endl;*/

    cout << "\n" << showbase << hex;
    if (get_file_data_clusters(file_MFT_number, file_index_clusters)) 
    {
        /*cout << "\ntest3\n" << endl;*/
        if (file_index_clusters.empty()) {
            cout << "文件数据属性常驻, 文件记录号为:\n\t" << file_MFT_number << "\n";
        } else {
            cout << "文件数据属性非常驻，占具簇号为:\n\t";
            for (const auto &a : file_index_clusters) cout << a << "，";
        }
        cout << "\n";
    } else {
        cerr << "\tno '" << complete_filename << "' exits ! or it's a directory!" 
            << endl;
    }
    cout << noshowbase << dec << endl;

}


int main(int argc, char **argv)
{
    if (argc != 4) {
        cerr << "\tUsage: elf -d dev filenmae" << endl;
        return 0;
    }
    string device = argv[2];
    string complete_filename = argv[3];

    getFileClusters_NTFS(complete_filename, device);

    return 0;
}
