
import  socket
import  os
import  select
#import  queue
import  _thread
import time 
from  struct import  *


"""
 test sunlands IM server client
 author:jackwu 
 
"""
"""
from google import  *
from IM.BaseDefine_pb2 import *
from IM.SwitchService_pb2 import *
from IM.Group_pb2 import *
from IM.Message_pb2 import *
from IM.Server_pb2 import *
from IM.Consult_pb2 import *
from IM.Other_pb2 import *
"""
from config import  *




def sendHeartbeat(sock):
 
    # msgheart = IMHeartBeat()
    # con = msgheart.SerializeToString()
    # lens = len(con)
    # #print(lens)
    # data = pack("!i6I",16 , 12, 12, SID_OTHER, CID_OTHER_HEARTBEAT, 0, 0)
    # while True:
    #    print("send heartbeat .........")
    #    sock.sendall(data.encode())
    #    time.sleep(1)
    #select all fd_sets
    readsets=[]
    writesets=[]
    exceptionsets=[]
    readsets.append(sock)
    writesets.append(sock)
    exceptionsets.append(sock)


    readsets ,writesets,exceptionsets =select.select(readsets,writesets,exceptionsets,3)
    for ready in readsets:
        if ready is sock:
            print("xxxxxxxxxready")

    pass


def start_select(sock):

    readsets=[]
    writesets=[]
    exceptionsets=[]
    readsets.append(sock)
    writesets.append(sock)
    exceptionsets.append(sock)

    while True:
        readsets ,writesets,exceptionsets =select.select(readsets,writesets,exceptionsets)
        for readmark in readsets:
            if readmark is sock: # client readable
                #create pthread
                #print("read")
                #readmark.sendall()
                #data=readmark.recv(1024)
                #print(data.decode())
                print("................readable........sleep(2).............")
                time.sleep(2)
                pass

        for writemark in writesets:
            if writemark is sock:
                #print("read")
                #pass
                #print("...............writeable........sleep(2).............")
                #writemark.sendall("encode".encode())
                #time.sleep(1)
                #_thread.start_new_thread(sendHeartbeat,(writemark,))
                pass


        for exceptionmark in exceptionsets:
            if exceptionmark is sock:
                #print("read")
                sock.close()
                pass




def start_client_server():
    #connect_info=("")
    #conf=config("config")
    #connection=(conf.get_value_string("ipaddr"),int(conf.get_value_int("port")))

    socket_client=socket.socket()
    if socket_client  == None:
        print("socket() error")
        socket_client.close()

    socket_client.setblocking(0)
    socket_client.settimeout(2)
    socket_client.connect(('172.16.103.125',20600))


    socket_client.setblocking(1)
    if socket_client==None:
        print("sock connection failed!")
        socket_client.close()
    #print(socket_client.fileno())
   # _thread.start_new_thread(sendHeartbeat, (socket_client,))#send heartbeat

    start_select(socket_client)




print(">>>>>>>>>")
start_client_server()





