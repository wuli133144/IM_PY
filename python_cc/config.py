
import  os
import  sys


class config(object):
    def __init__(self,filepath):
        self.m_fpath=filepath
        self.m_dict={}
        self.init()

    def init(self):
        bexit = os.path.exists(self.m_fpath)
        if bexit is not True:
         return False
        contents=[]
        with open(self.m_fpath,"r") as f:
            contents=f.readlines()
            pass


        for i in range(len(contents)):
            #print(len(contents))
            #print(contents[i].strip())[0])
            contents[i]=contents[i].strip()
            if len(contents[i])==0 :
                continue
            #print(i)

            if  "#"  not in contents[i]:
                temp_key_value=contents[i].split("=")
                self.m_dict[temp_key_value[0].strip()]=temp_key_value[1].strip()


    """
     #key1=xx
     #key3=yy
    """
    def get_value_string(self,keys):
        if isinstance(keys,str) is False:
            return  None
        item=self.m_dict.get(keys)
        return item

    def get_value_int(self,keys):
        if isinstance(keys,str) is False:
            return  None
        item=self.m_dict.get(keys)
        return item

    def __repr__(self):
        print(self.m_dict)