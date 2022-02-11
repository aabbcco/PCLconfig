import os


# list libs for Boost FLANN and GTK 
def listIncludeLibCommon(dir:str):
    lister = ['Boost','FLANN','VTK']
    libs= [file+'\n' for list in lister for _,_,files in os.walk(os.path.join(dir,list,'lib')) for file in files if file.endswith('.lib') ]

    debug_list = [lib for lib in libs if 'gd' in lib]
    release_list = [lib for lib in libs if 'gd' not in lib]

    release_list.append('OpenNI2.lib\n')
    debug_list.append('OpenNI2.lib\n')
    return release_list,debug_list

def listIncludeLibQhull(dir:str):
    libs = [file+'\n' for _,_,files in os.walk(os.path.join(dir,'Qhull/lib')) for file in files if file.endswith('.lib') ]
    debug_list = [lib for lib in libs if 'd' in lib]
    release_list = [lib for lib in libs if 'd' not in lib]

    return release_list,debug_list
    
def listIncludeLibPcl(dir:str):
    return [file+'\n'  for _,_,files in os.walk(os.path.join(dir,'lib')) for file in files if file.endswith('.lib') ]

release_list,debug_list = listIncludeLibCommon(os.path.join(os.environ['PCL_ROOT'],'3rdParty'))
release_q,debug_q = listIncludeLibQhull(os.path.join(os.environ['PCL_ROOT'],'3rdParty'))
pcl_list = listIncludeLibPcl(os.environ['PCL_ROOT'])

release_list.extend(release_q)
debug_list.extend(debug_q)
release_list.extend(pcl_list)
debug_list.extend(pcl_list)

with open('release_list.txt','w') as fp:
    fp.writelines(release_list)
with open('debug_list.txt','w') as fp:
    fp.writelines(debug_list)