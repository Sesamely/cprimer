/************************************************************************
****	> File Name:    	Markdown_to_Html.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	2018年03月17日 星期六 13时58分25秒
************************************************************************/

#include <iostream>
#include <sstream>
using namespace std;


void cout_content(ostream &out, string line) {
    int line_char_number = line.size();
    bool has_meet_underline = false;
    string link_content = "";
    for (int i=0; i<line_char_number; ++i) {
        if (line[i] == '_') {
            if (!has_meet_underline) {
                has_meet_underline = true;
                out << "<em>";
            } else {
                has_meet_underline = false;
                out << "</em>";
            }
            continue;
        }
        if (line[i] == '\x5B') {
            out << "<a href=\"";
            link_content = "";
            for (++i; line[i] != ']'; ++i) {
                link_content += line[i];
            }
            i += 2;
            for (; line[i] != ')'; ++i) {
                out << line[i];
            }
            out << "\">";
            cout_content(out, link_content);
            out << "</a>";
            continue;
        }

        out << line[i];
    }
}

int main()
{
    ostream &out = cout;
    string pre_statement_type = "";
    string this_statement_type = "";
    string line;

    while (getline(cin, line)) {

        pre_statement_type = this_statement_type;
        if (line == "") {
            this_statement_type = "";
            if (pre_statement_type == "p")
                out << "</p>\n";
            else if (pre_statement_type == "u") {
                out << "</ul>\n";
            }
            continue;
        }

        this_statement_type = "p";
        int cur_line_char_number = line.size();
        for (int i=0; i<cur_line_char_number; ++i) {
            if (line[i] == '#') {
                this_statement_type = "h";
                break;
            }
            if (line[i] == '*') {
                this_statement_type = "u";
                break;
            }
        }

        if(this_statement_type == "h") {
            int number = 0;
            int i;
            for (i=0; line[i]==' '||line[i]=='#'; ++i) {
                if (line[i] == '#') ++number;
            }
            string content = "";
            for (; i<cur_line_char_number; ++i) {
                content += line[i];
            }
            out << "<h" << number << ">";
            cout_content(cout, content);
            out << "</h" << number << ">\n";
        }
        if (this_statement_type == "u") {
            string content;
            int i=1;
            for (; line[i]==' '; ++i);
            for (; i<cur_line_char_number; ++i) {
                content += line[i];
            }
            if (pre_statement_type != "u") {
                out << "<ul>\n" << "<li>";
                cout_content(cout, content);
                out << "</li>\n";
            } else {
                out << "<li>";
                cout_content(cout, content);
                out << "</li>\n";
            }
        }
        if (this_statement_type == "p") {
            if (pre_statement_type == "p") {
                out << "\n";
                cout_content(cout, line);
            } else {
                out << "<p>";
                cout_content(cout, line);
            }
        }   
    }
    if (this_statement_type == "p") {
        out << "</p>\n";
    }
    if (this_statement_type == "u") {
        out << "</ul>\n";
    }

    return 0;
}
