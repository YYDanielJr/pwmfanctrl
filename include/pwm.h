/*
 * @Author: Y.Y. Daniel 626986815@qq.com
 * @Date: 2024-04-25 22:37:46
 * @LastEditors: Y.Y. Daniel 626986815@qq.com
 * @LastEditTime: 2024-04-26 20:03:25
 * @FilePath: /pwmfanctrl/include/pwm.h
 * @Description: 调用系统pwm的主函数
 */

#pragma once
#include <string>
#include <cstdint>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH_NOT_SET 255
#define UNABLE_TO_OPEN_FOLDER 1
#define EXPORT_WRITE_ERROR 2
#define UNABLE_TO_READ_FOLDER -1
#define PARA_READ_ERROR -2

class Pwm {
private:
    std::string pwmPath;
public:
    Pwm();
    Pwm(std::string path);
    Pwm(int pwmchip);
    int initialize();
    int changePwmPath(std::string path);
    int enable();
    int setPeriod(uint32_t period);
    int setDutyCycle(uint32_t dutyCycle);
    int disable();
    int saveProfile(std::string profileName);
    uint32_t getPeriod();
    uint32_t getDutyCycle();
};

uint32_t stou(char* str);