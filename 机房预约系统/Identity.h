#pragma once//防止头文件包含
#include<iostream>
using namespace std;
// 身份抽象类 
class Identity {
public:
    //操作菜单 纯虚函数
    virtual void operMenu() = 0;
    //用户名
    string m_Name;
    //密码
    string m_Pwd;
    //初始化机房信息
    virtual void initComputerRoom() = 0;
};