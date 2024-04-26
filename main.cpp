/*
 * @Author: Y.Y. Daniel 626986815@qq.com
 * @Date: 2024-04-25 22:35:59
 * @LastEditors: Y.Y. Daniel 626986815@qq.com
 * @LastEditTime: 2024-04-26 23:21:28
 * @FilePath: /pwmfanctrl/main.cpp
 * @Description: 主函数，采用命令形式
 * 命令用法：pwmfanctrl --pwmchip X （进入交互式界面，设置周期和占空比）
 * pwmfanctrl --pwmchip X --set-period <period> --set-duty-cycle <duty-cycle> [--save-profile <profile_path_name>]
 * pwmfanctrl --pwmchip X --set-percentage <percentage> [--save-profile <profile_path_name>] （此时默认周期为1000000）
 * pwmfanctrl --load-profile <profile_path_name>
 * pwmfanctrl --pwmchip X --stop （将占空比设置与周期相等，并把enable设置为0）
 * 一旦命令成功执行，pwm自动启动。
 */

#include <iostream>
#include "include/pwm.h"

int main(int argc, char** argv){
    if(argc == 1) {
        std::cerr << "You can use \"pwmfanctrl -h\" to look for more help." << std::endl;
        exit(2);
    }
    else {
        int pwmchipNumber;
        uint32_t period;
        uint32_t duty_cycle;
        if(argv[1] == "--load-profile") {
            if(argc == 2) {
                std::cerr << "Missing necessary argument." << std::endl;
                exit(2);
            }
            else {

            }
        }
        else if(argv[1] == "--pwmchip") {
            if(argc == 2) {
                
            }
            else {

            }
        }
        else {
            std::cerr << "Invalid argument: " << argv[1] << std::endl;
            exit(2);
        }
    }
}
