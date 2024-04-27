/*
 * @Author: Y.Y. Daniel 626986815@qq.com
 * @Date: 2024-04-25 22:35:59
 * @LastEditors: Y.Y. Daniel 626986815@qq.com
 * @LastEditTime: 2024-04-27 16:44:33
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
#include <cstring>
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
            if(argc == 2) { // 参数错误
                std::cerr << "Missing necessary argument." << std::endl;
                exit(2);
            }
            else {

            }
        }
        else if(strcmp(argv[1], "--pwmchip") == 0) {
            if(argc == 3 && isDigit(argv[2])) {    // 需要进入交互界面，输入周期和占空比
                std::cout << "Please input the period and the duty cycle: " << std::endl;
                std::cin >> period >> duty_cycle;
                Pwm pwm(stoi(argv[2]));
                return pwm.quickStart(period, duty_cycle);
            }
            else if(argc == 4 && strcmp(argv[3], "--stop") == 0) {
                Pwm pwm(stoi(argv[2]));
                return pwm.quickStart(1000000, 1000000);
            }
            else if(argc == 5 && strcmp(argv[3], "--set-percentage") == 0) {    // 提供百分比，默认以1000000的周期计算
                Pwm pwm(stoi(argv[2]));
                period = 1000000;
                duty_cycle = period / 100 * stou(argv[4]);
                return pwm.quickStart(period, duty_cycle);
            }
            else if(argc == 7 && strcmp(argv[5], "--save-profile") == 0) {    // 提供占空比和周期，直接设置
                Pwm pwm(stoi(argv[2]));
                return pwm.quickStart(stou(argv[4]), stou(argv[6]));
            }
            else if(argc == 7 && (strcmp(argv[5], "--set-duty-cycle") == 0 || strcmp(argv[5], "--set-period") == 0)) {    // 提供占空比和周期，直接设置
                if(strcmp(argv[3], "--set-duty-cycle") == 0) {
                    duty_cycle = stou(argv[4]);
                }
                if(strcmp(argv[3], "--set-period") == 0) {
                    period = stou(argv[4]);
                }
                if(strcmp(argv[5], "--set-duty-cycle") == 0) {
                    duty_cycle = stou(argv[6]);
                }
                if(strcmp(argv[5], "--set-period") == 0) {
                    period = stou(argv[6]);
                }
                Pwm pwm(stoi(argv[2]));
                return pwm.quickStart(period, duty_cycle);
            }
            else if(argc == 9) {    // 设置占空比，并保存配置，这里的命令判断还不完善
                if(strcmp(argv[3], "--set-duty-cycle") == 0) {
                    duty_cycle = stou(argv[4]);
                }
                if(strcmp(argv[3], "--set-period") == 0) {
                    period = stou(argv[4]);
                }
                if(strcmp(argv[5], "--set-duty-cycle") == 0) {
                    duty_cycle = stou(argv[6]);
                }
                if(strcmp(argv[5], "--set-period") == 0) {
                    period = stou(argv[6]);
                }
                Pwm pwm(stoi(argv[2]));
                return pwm.quickStart(period, duty_cycle);
            }
            else {
                std::cerr << "Invalid argument. " << std::endl;
                exit(2);
            }
        }
        else {
            std::cerr << "Invalid argument: " << argv[1] << std::endl;
            exit(2);
        }
    }
}
