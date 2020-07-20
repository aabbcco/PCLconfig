#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

int main()
{

  string str_to_define;
  ifstream list;
  ofstream debug_list, release_list;

  cout << "欢迎使用PCL Visual Studio依赖项配置工具，本程序根据BSD协议开源" << endl;
  /*get link list */
  /*PCL itself and qhull requires different treatment, it has different ways to differ debug and release */
  system("dir /b .\\lib\\*.lib >list_pcl.txt");                    //PCL itself
  system("dir /b .\\3rdParty\\Qhull\\lib\\*.lib >list_qhull.txt"); //qhull

  /* waiting the file to be create */
  cout << "sleep start at: " << time(NULL) << endl;
  _sleep(2000);
  cout << "sleep stop at: " << time(NULL) << endl;

  /* differ debug and release lib in boost/VTK/FLANN */
  list.open("list.txt");
  debug_list.open("debug_list.txt");
  debug_list << "将以下内容复制粘贴至debug的链接依赖项中：" << endl;
  release_list.open("release_list.txt");
  release_list << "将以下内容 复制粘贴至relrase的依赖项中：" << endl;
  for (unsigned int i = 0; i < 3; i++)
  {
    switch (i)
    {
      /* dir will clean list.txt every time you use it so we should execute it differently */
    case 0:
    {
      system("dir /b .\\3rdParty\\Boost\\lib\\*.lib >list.txt");
      cout<<"case1"<<endl;
      break;
    }
    case 1:
    {
      system("dir /b .\\3rdParty\\FLANN\\lib\\*.lib >list.txt");
      cout<<"case2"<<endl;
      break;
    }
    case 2:
    {
      cout<<"case3"<<endl;
      system("dir /b .\\3rdParty\\VTK\\lib\\*.lib >list.txt");
      break;
    }
    }
    cout<<"start list sleep"<<endl;
    _sleep(1000);
    cout<<"stop list sleep"<<endl;
    list.open("list.txt");
    while (!list.eof())
    {

      getline(list, str_to_define);
      //using gd to differ lists
      if (str_to_define.find("gd") != string::npos)
      {
        debug_list << str_to_define << endl;
      }
      else
      {
        release_list << str_to_define << endl;
      }
    }
    list.close();
  }

  /* start to differ PCL itself */
  list.open("list_pcl.txt");
  while (!list.eof())
  {
    getline(list, str_to_define);
    //using debug or release to differ libs
    if (str_to_define.find("debug") != string::npos)
    {
      debug_list << str_to_define << endl;
    }
    else
      release_list << str_to_define << endl;
  }
  list.close();

  /* start to differ Qhull */
  list.open("list_qhull.txt");
  while (!list.eof())
  {
    getline(list, str_to_define);
    //using debug or release to differ libs
    if (str_to_define.find("_d") != string::npos)
    {
      debug_list << str_to_define << endl;
    }
    else
      release_list << str_to_define << endl;
  }

  release_list.close();
  debug_list.close();
  cout << "process done!";
  system("pause");

  return 0;
}


