/*
 * @Author: Y.Y. Daniel 626986815@qq.com
 * @Date: 2024-04-25 22:37:14
 * @LastEditors: Y.Y. Daniel 626986815@qq.com
 * @LastEditTime: 2024-04-26 23:34:04
 * @FilePath: /pwmfanctrl/src/pwm.cpp
 * @Description: 调用系统pwm的主函数
 */

#include "../include/pwm.h"

Pwm::Pwm() {

}
Pwm::Pwm(std::string path) {
    pwmPath = path;
}
Pwm::Pwm(int pwmchip) {
    pwmPath = "/sys/class/pwm/pwmchip" + pwmchip;
    
}

int Pwm::changePwmPath(std::string path)
{
    pwmPath = path;
    return 0;
}
int Pwm::initialize() {
    if(pwmPath.find("/sys/class/pwm/pwmchip") == std::string::npos) {
        return PATH_NOT_SET;
    }

    if(access((pwmPath + std::string("/pwm0")).c_str(), F_OK)) {    // 检测是否已经被打开，如果没有被打开就导出
        int fd = open(pwmPath.c_str(), O_WRONLY);   
        if(fd < 0) {
            return UNABLE_TO_OPEN_FOLDER;
        }
        if(write(fd, "0", 1) != 1) {
            return EXPORT_WRITE_ERROR;
        }
        close(fd);
    }
    pwmPath += "/pwm0";
}
int Pwm::enable()
{
    int fd = open((pwmPath + "/enable").c_str(), O_WRONLY);
    if(fd < 0) {
        return UNABLE_TO_OPEN_FOLDER;
    }
    if(write(fd, "0", 1) != 1) {
        return EXPORT_WRITE_ERROR;
    }
    close(fd);
    return 0;
}

int Pwm::setPeriod(uint32_t period)
{
    int fd = open((pwmPath + "/period").c_str(), O_WRONLY);
    if(fd < 0) {
        return UNABLE_TO_OPEN_FOLDER;
    }
    if(write(fd, std::to_string(period).c_str(), std::to_string(period).length()) != std::to_string(period).length()) {
        return EXPORT_WRITE_ERROR;
    }
    close(fd);
    return 0;
}

int Pwm::setDutyCycle(uint32_t dutyCycle)
{
    int fd = open((pwmPath + "/duty_cycle").c_str(), O_WRONLY);
    if(fd < 0) {
        return UNABLE_TO_OPEN_FOLDER;
    }
    if(write(fd, std::to_string(dutyCycle).c_str(), std::to_string(dutyCycle).length()) != std::to_string(dutyCycle).length()) {
        return EXPORT_WRITE_ERROR;
    }
    close(fd);
    return 0;
}

int Pwm::disable()
{
    // 这里之后再写，要写的是
    int fd = open((pwmPath + "/enable").c_str(), O_WRONLY);
    if(fd < 0) {
        return UNABLE_TO_OPEN_FOLDER;
    }
    if(write(fd, "0", 1) != 1) {
        return EXPORT_WRITE_ERROR;
    }
    close(fd);
    return 0;
}

int Pwm::saveProfile(std::string profileName)
{
    return 0;
}

uint32_t Pwm::getPeriod() {
    int fd = open((pwmPath + "/period").c_str(), O_WRONLY);
    char buf[100] = {0};
    if(fd < 0) {
        return UNABLE_TO_READ_FOLDER;
    }
    if(read(fd, buf, 100) <= 0) {
        return EXPORT_WRITE_ERROR;
    }
    close(fd);
    return stou(buf);
}

uint32_t Pwm::getDutyCycle() {
    int fd = open((pwmPath + "/duty_cycle").c_str(), O_WRONLY);
    char buf[100] = {0};
    if(fd < 0) {
        return UNABLE_TO_READ_FOLDER;
    }
    if(read(fd, buf, 100) <= 0) {
        return EXPORT_WRITE_ERROR;
    }
    close(fd);
    return stou(buf);
}

int Pwm::quickStart(uint32_t period, uint32_t dutyCycle) {
    initialize();
    setPeriod(period);
    setDutyCycle(dutyCycle);
    enable();
    return 0;
}

// 字符串转uint32_t
uint32_t stou(char* str) {
    uint32_t ret = 0;
    int i = 0;
    while(str[i] != 0) {
        i++;
    }
    i--;
    for(;i >= 0; i--) {
        ret += 10 * ret + str[i];
    }
    return ret;
}

int stoi(char* str) {
    int ret = 0;
    int i = 0;
    while(str[i] != 0) {
        i++;
    }
    i--;
    for(;i >= 0; i--) {
        ret += 10 * ret + str[i];
    }
    return ret;
}

bool isDigit(char* str) {
    for(int i = 0; i < strlen(str); i++) {
        if(!(str[i] >= '0' && str[i] <= '9')) {
            return false;
        }
    }
    return true;
}