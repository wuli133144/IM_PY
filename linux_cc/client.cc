#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <memory>
#include <boost/asio.hpp>
#include <limits.h>

#include "public_define.h"
#include "ImPduBase.h"
#include "BaseSocket.h"
#include "StringUtils.h"

#include "IM.BaseDefine.pb.h"
#include "IM.Live.pb.h"
#include "IM.RPC.pb.h"
#include "IM.Other.pb.h"
#include "IM.Message.pb.h"
#include "ConfigFileReader.h"

using boost::asio::ip::tcp;
using namespace IM::BaseDefine;
using namespace IM::Live;


typedef std::deque<CImPdu> chat_message_queue;



class chat_client:public std::enable_shared_from_this<chat_client>
{
public:
	
  chat_client(boost::asio::io_service& io_service,
      const boost::asio::ip::tcp::endpoint& endpoints)
     : io_context_(io_service),
      socket_(io_service)
     
  {
     m_thread_heartbeat=NULL;
     do_connect(endpoints);
	
  }
	  
  ~chat_client(){
  
    if(NULL!=m_thread_heartbeat){
		 delete m_thread_heartbeat;
		 m_thread_heartbeat=NULL;
	}
	
  }
  void write(const CImPdu & msg)
  {    
        io_context_.post(
        [this, &msg]()
        { 
          //std::cout<<"xxxxx"<<std::endl;
          bool write_in_progress = !write_msgs_.empty();
          write_msgs_.push_back(msg);
          if (!write_in_progress)
          {
            do_write();
          }
        });
  }
  
  //!  create liveroom test async_create_liveroom
  //!  recent createliveroom impl has't resolve
  //！ issues between tars and teamtalk,you know tengcent's tars 
  //!  structure need a current transport object,it contains 
  //!  ip port,functionname and so on,but this client test
  //!  can't create tarsinfo.
  #if 0 
  void CreateLiveRoom(uint32_t live_id,uint32_t user_id,uint32_t capacitys){
     CImPdu pPdu;
	 IM::RPC::IMRPCCreateLiveChatRoomReq msg;
     msg.set_live_id(live_id);
	 msg.set_user_im_id(user_id);
	 msg.set_live_capacity(capacitys);
	 IM::RPC::TarsInfo* pTarsInfo = msg.mutable_tars_info();
     pTarsInfo->set_fd(1);
     pTarsInfo->set_uid(2);
     pTarsInfo->set_request_id(2);
     pTarsInfo->set_port(2000);
     pTarsInfo->set_ip("www.baidu.com");
     pPdu.SetPBMsg(&msg);
     pPdu.SetServiceId(SID_RPC);
	 pPdu.SetCommandId(CID_RPC_CREATE_LIVEROOM_MSG_REQUEST);
	 
	 write(pPdu);
      
  }
 #endif
  void close()
  {
    io_context_.post([this]() { socket_.close(); });
  }

private:
  void do_connect(const boost::asio::ip::tcp::endpoint& endpoints)
  {
        socket_.async_connect(endpoints,
        [this](const boost::system::error_code ec)
        {
          if (!ec)
          {
            do_read_header();
			std::cout<<"link success start heartbeat"<<std::endl;
			if(!m_thread_heartbeat){
				 m_thread_heartbeat=new thread([this](){
			     while(1){
			      hearbeat();
			      usleep(5000*1000);
			     }
		   
		   });
				}
          	}
	    });
        
       
  }

  void do_read_header()
  {
        boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.GetBuffer(),IM_PDU_HEADER_LEN),
        [this](const boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read_body();
          }
          else
          {
            socket_.close();
          }
        });
  }

  void do_read_body()
  {     
        boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.GetBodyData(), read_msg_.GetBodyLength()),
        [this](const boost::system::error_code  ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            //std::cout.write(read_msg_.body(), read_msg_.body_length());
            //std::cout << "\n";
            do_read_header();
          }
          else
          {
            socket_.close();
          }
        });
  }

  void do_write()
  {      
        //std::cout<<"do_write_"<<std::endl;
        //auto self(shared_from_this());
		if(!write_msgs_.empty()){
		 // std::cout<<"[write_msg_]"<<write_msgs_.size()<<std::endl;
		}
		
        boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().GetBuffer(),
          write_msgs_.front().GetLength()),
        [this](const boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          { 
            std::cout<<"do_write_pop_front over callback start"<<std::endl; 
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
              do_write();
            }
          }
          else
          {
            socket_.close();
          }
        });
  }

  void hearbeat(){

		IM::Other::IMHeartBeat msg;
		
        CImPdu pdu;
        pdu.SetPBMsg(&msg);
        pdu.SetServiceId(SID_OTHER);
        pdu.SetCommandId(CID_OTHER_HEARTBEAT);
		//SendPdu(&pdu);
		write(pdu);
  }
  
private:
  boost::asio::io_service& io_context_;
  boost::asio::ip::tcp::socket socket_;
  CImPdu read_msg_;
  chat_message_queue write_msgs_;
  thread *m_thread_heartbeat;
};



void helper()
{
        std::cout<<"TARS and TeamTalk test function"<<std::endl;
		std::cout<<"select 1 :test create live room"<<std::endl;
		std::cout<<"select 2 :test close live room"<<std::endl;
}



int user_containers[]={
	6450,
	1857024,
	1857028,
	1857029,
	3525971,
	3525972,
	3525973,
	3525974,
	3525975,
	3525976,
	3525977,
	3525978,
	3525979,
	3525980,
	3525981,
	3525982,
	3525983,
	3525984,
	3525985,
	3525986,
	3525987,
	3525988,
	3525989,
	3525990,
	3525991,
	3525992,
	3525993,
	3525994,
	3525995,
	3525996,
	3525997,
	3525998,
	3525999,
	3526000,
	3526001,
	3526002,
	3526003,
	3526004,
	3526005,
	3526006,
	3526007,
	3526008,
	3526009,
	3526010,
	3526011,
	3526012,
	3526013,
	3526014,
	3526015,
	3526016,
	3526017,
	3526018,
	3526019,
	3526020,
	3526021,
	3526022,
	3526023,
	3526024,
	3526025,
	3526026,
	3526027,
	3526028,
	3526029,
	3526030,
	3526031,
	3526032,
	3526033,
	3526034,
	3526035,
	3526036,
	3526037,
	3526038,
	3526039,
	3526040,
	3526041,
	3526042,
	3526043,
	3526044,
	3526045,
	3526046,
	3526047,
	3526048,
	3526049,
	3526050,
	3526051,
	3526052,
	3526053,
	3526054,
	3526055,
	3526056,
	3526057,
	3526058,
	3526059,
	3526060,
	3526061,
	3526062,
	3526063,
	3526064,
	3526065,
	3526066,
	3526067,
	3526068,
	3526069,
	3526070,
	3526071,
	3526072,
	3526073,
	3526074,
	3526075,
	3526076,
	3526077,
	3526078,
	3526079,
	3526080,
	3526081,
	3526082,
	3526083,
	3526084,
	3526085,
	3526086,
	3526087,
	3526088,
	3526089,
	3526090,
	3526091,
	3526092,
	3526093,
	3526094,
	3526095,
	3526096,
	3526097,
	3526098,
	3526099,
	3526100,
	3526101,
	3526102,
	3526103,
	3526104,
	3526105,
	3526106,
	3526107,
	3526108,
	3526109,
	3526110,
	3526111,
	3526112,
	3526113,
	3526114,
	3526115,
	3526116,
	3526117,
	3526118,
	3526119,
	3526120,
	3526121,
	3526122,
	3526123,
	3526124,
	3526125,
	3526126,
	3526127,
	3526128,
	3526129,
	3526130,
	3526131,
	3526132,
	3526133,
	3526134,
	3526135,
	3526136,
	3526137,
	3526138,
	3526139,
	3526140,
	3526141,
	3526142,
	3526143,
	3526144,
	3526145,
	3526146,
	3526147,
	3526148,
	3526149,
	3526150,
	3526151,
	3526152,
	3526153,
	3526154,
	3526155,
	3526156,
	3526157,
	3526158,
	3526159,
	3526160,
	3526161,
	3526162,
	3526163,
	3526164,
	3526165,
	3526166,
	3526167,
	3526168,
	3526169,
	3526170,
	3526171,
	3526172,
	3526173,
	3526174,
	3526175,
	3526176,
	3526177,
	3526178,
	3526179,
	3526180,
	3526181,
	3526182,
	3526183,
	3526184,
	3526185,
	3526186,
	3526187,
	3526188,
	3526189,
	3526190,
	3526191,
	3526192,
	3526193,
	3526194,
	3526195,
	3526196,
	3526197,
	3526198,
	3526199,
	3526200,
	3526201,
	3526202,
	3526203,
	3526204,
	3526205,
	3526206,
	3526207,
	3526208,
	3526209,
	3526210,
	3526211,
	3526212,
	3526213,
	3526214,
	3526215,
	3526216,
	3526217,
	3526218,
	3526219,
	3526220,
	3526221,
	3526222,
	3526223,
	3526224,
	3526225,
	3526226,
	3526227,
	3526228,
	3526229,
	3526230,
	3526231,
	3526232,
	3526233,
	3526234,
	3526235,
	3526236,
	3526237,
	3526238,
	3526239,
	3526240,
	3526241,
	3526242,
	3526243,
	3526244,
	3526245,
	3526246,
	3526247,
	3526248
	
};




const int group_id=6545;

int random_index()
{
     return  random()%(sizeof(user_containers)/sizeof(int));
}


int random_index_plus(unsigned int range)
{
  if(range > sizeof(user_containers)/sizeof(int))
  	 return random()%(sizeof(user_containers)/sizeof(int));
  return random()%(range);
}


int msgid()
{
     return random()%(INT_MAX);
}

int main(int argc, char* argv[])
{
  try
  {
   
    srand(time(NULL));
	signal(SIGPIPE,SIG_IGN);
  
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
	
	CConfigFileReader config("client_netinfo.conf");
	char* ipstr=config.GetConfigName("ServerIP1");
	char* portstr=config.GetConfigName("ServerPort1");
	boost::asio::ip::tcp::socket socket(io_service);
	//socket(io_service);
    boost::asio::ip::tcp::endpoint endpoints(boost::asio::ip::address::from_string(ipstr), std::atoi(portstr));
    socket.connect(endpoints);
	  
	std::thread t([&io_service]{ io_service.run();});
	std::thread f([&]{
	while(1){
		
	    IM::Other::IMHeartBeat msg;
        CImPdu pdu;
        pdu.SetPBMsg(&msg);
        pdu.SetServiceId(SID_OTHER);
        pdu.SetCommandId(CID_OTHER_HEARTBEAT);
		
	    socket.send(boost::asio::buffer(pdu.GetBuffer(),pdu.GetLength()));
		usleep(5000*1000);}
	
	});
	
	 //模式群内人员快速随机的发送ack
     int g_send_count=0,g_range_count=0;
     std::thread work([&]{
	       std::cout<<"test msg ack Cache function"<<std::endl;
		    while (1){
                std::cout<<"send msg ack........."<<g_send_count++<<std::endl;
				IM::Message::IMMsgDataAck msg;
				msg.set_user_id(user_containers[random_index()]);
				msg.set_session_id(group_id);
				msg.set_msg_id(msgid());
				msg.set_create_time((uint64_t)time(NULL));
				msg.set_session_type(2);
				msg.set_result_code(0);
				
				
				CImPdu pdu;
			    pdu.SetPBMsg(&msg);
			    pdu.SetServiceId(SID_MSG);                            
			    pdu.SetCommandId(CID_MSG_DATA_ACK);
				socket.send(boost::asio::buffer(pdu.GetBuffer(),pdu.GetLength()));
	            usleep(100*1000);
	           }
		   
           
	 });
			
    //模拟少数相同的成员不停发送ack
	 std::thread work1([&]{
		std::cout<<"test msg ack range Cache function"<<std::endl;
		while (1){
			std::cout<<"send range ack........."<<g_range_count++<<std::endl;
			IM::Message::IMMsgDataAck msg;
			msg.set_user_id(user_containers[random_index_plus(3)]);
			msg.set_session_id(group_id);
			msg.set_msg_id(msgid());

			msg.set_create_time((uint64_t)time(NULL));
			msg.set_session_type(2);
			msg.set_result_code(0);


			CImPdu pdu;
			pdu.SetPBMsg(&msg);
			pdu.SetServiceId(SID_MSG);
			pdu.SetCommandId(CID_MSG_DATA_ACK);
			socket.send(boost::asio::buffer(pdu.GetBuffer(),pdu.GetLength()));
			usleep(100*1000);
		}
		   
           
	 });
	 
     #if 0
	      std::thread work1([&]{
	       std::cout<<"test msg ack Cache function"<<std::endl;
		    
		    IM::Message::IMMsgDataAck msg;
			msg.set_user_id(3662415);
			msg.set_session_id(7899);
			msg.set_msg_id(12);

			msg.set_create_time((uint64_t)time(NULL));
			msg.set_session_type(2);
			msg.set_result_code(0);
			
			
			CImPdu pdu;
		    pdu.SetPBMsg(&msg);
		    pdu.SetServiceId(SID_MSG);
		    pdu.SetCommandId(CID_MSG_DATA_ACK);
			socket.send(boost::asio::buffer(pdu.GetBuffer(),pdu.GetLength()));
		   
           
	 });

	    std::thread work2([&]{
	       std::cout<<"test msg ack Cache function"<<std::endl;
		    
		    IM::Message::IMMsgDataAck msg;
			msg.set_user_id(3662413);
			msg.set_session_id(7899);
			msg.set_msg_id(12);

			msg.set_create_time((uint64_t)time(NULL));
			msg.set_session_type(2);
			msg.set_result_code(0);
			
			
			CImPdu pdu;
		    pdu.SetPBMsg(&msg);
		    pdu.SetServiceId(SID_MSG);
		    pdu.SetCommandId(CID_MSG_DATA_ACK);
			socket.send(boost::asio::buffer(pdu.GetBuffer(),pdu.GetLength()));
		   
           
	 });
	 //1816394 1858937 1859909 1860721

	    std::thread work3([&]{
	       std::cout<<"test msg ack Cache function"<<std::endl;
		    
		    IM::Message::IMMsgDataAck msg;
			msg.set_user_id(3662412);
			msg.set_session_id(7899);
			msg.set_msg_id(12);

			msg.set_create_time((uint64_t)time(NULL));
			msg.set_session_type(2);
			msg.set_result_code(0);
			
			
			CImPdu pdu;
		    pdu.SetPBMsg(&msg);
		    pdu.SetServiceId(SID_MSG);
		    pdu.SetCommandId(CID_MSG_DATA_ACK);
			socket.send(boost::asio::buffer(pdu.GetBuffer(),pdu.GetLength()));
		   
           
	 });
	  std::thread work4([&]{
	       std::cout<<"test msg ack Cache function"<<std::endl;
		    
		    IM::Message::IMMsgDataAck msg;
			msg.set_user_id(5001);
			msg.set_session_id(7899);
			msg.set_msg_id(12);

			msg.set_create_time((uint64_t)time(NULL));
			msg.set_session_type(2);
			msg.set_result_code(0);
			
			
			CImPdu pdu;
		    pdu.SetPBMsg(&msg);
		    pdu.SetServiceId(SID_MSG);
		    pdu.SetCommandId(CID_MSG_DATA_ACK);
			socket.send(boost::asio::buffer(pdu.GetBuffer(),pdu.GetLength()));
		   
           
	 });
	
	 	
	 	
	
	//socket.send(boost::asio::buffer())

#endif
	 
     t.join();
	 f.join();
	 work.join();
	 work1.join();
	 /*rk.join();
	 work1.join();
	 work2.join();
	 work3.join();
	 work4.join();
	 */

	 
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  
  return 0;
}
