#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"

int main(int argc, char **argv)
{
    // 初始化框架
    MprpcApplication::Init(argc, argv);

    lzh::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法的请求
    lzh::LoginRequest request;
    request.set_name("li wei");
    request.set_pwd("123456");

    // rpc方法的响应
    lzh::LoginResponse response;
    // 发起rpc方法的调用， 同步的rpc调用过程 
    MprpcController controller;
    stub.Login(&controller, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有的数据序列化、反序列化和网络发送

    // 一次rpc调用完成，读调用的结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (0 == response.result().errcode())
        {
            std::cout << "rpc Login response sucess:" << response.sucess() << std::endl;
        }
        else
        {
            std::cout << "rpc login response error:" << response.result().errmsg() << std::endl;
        }
        
        
    }
    // lzh::RegisterRequest req;
    // req.set_id(2000);
    // req.set_name("lin zhonghui");
    // req.set_pwd("666666");
    // lzh::RegisterResponse rsp;
    // stub.Register(nullptr, &req, &rsp, nullptr);
    // // 一次rpc调用完成，读调用的结果
    // if (0 == rsp.result().errcode())
    // {
    //     std::cout << "rpc Register response sucess:" << rsp.sucess() << std::endl;
    // }
    // else
    // {
    //     std::cout << "rpc Register response error:" << rsp.result().errmsg() << std::endl;
    // }
    return 0;
}