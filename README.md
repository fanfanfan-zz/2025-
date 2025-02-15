# 学生成绩信息管理系统
这是一个出于学习目的而开发的简单的c语言学生成绩信息管理系统，由于本人c语言学习时长有限，水平有限，该代码还十分简陋，还有很多功能为完善，日后有可能会进一步优化该系统

---

## 目录
- [学生成绩信息管理系统](#学生成绩信息管理系统)
  - [目录](#目录)
  - [功能列表](#功能列表)
  - [安装步骤](#安装步骤)
    - [1. 克隆仓库](#1-克隆仓库)
    - [2. 安装编译工具](#2-安装编译工具)
    - [3. 编译项目](#3-编译项目)
    - [4. 运行项目](#4-运行项目)
  - [使用方法](#使用方法)
  - [项目截图](#项目截图)


---

## 功能列表

- **学生信息管理**：
  - 添加学生信息（姓名、学号、各科成绩）。
  - 删除学生信息。
  - 修改学生信息。
  - 查询学生信息。
- **成绩统计与排名**：
  - 计算每个学生的平均成绩。
  - 按平均成绩对学生进行排名。
  - 显示所有学生的排名信息。
- **班级成绩统计**：
  - 统计并显示班级的最高分、最低分和平均分。
- **文件操作**
  - 将学生的信息保存到文件中：students.txt  
  - 从文件中读取学生信息并加载到程序中

---

## 安装步骤

### 1. 克隆仓库
打开终端，运行以下命令克隆项目到本地：
```bash
git clone https://github.com/fanfanfan-zz/2025-
```

### 2. 安装编译工具
确保系统中已安装 gcc 编译器。如果未安装，运行以下命令安装：
```bash
sudo apt update
sudo apt install gcc
```
### 3. 编译项目
```bash
cd /home/zy/github2025/2025-/week1-简易学生成绩管理系统
gcc -o sms 1.cpp
```
注意这里的 `cd` 指令是进入到你clone时安装的路径，需要自己输入文件路径进入到1.cpp所在的文件夹，另外第二段代码中的**sms**指的是给这个编译后得到的可知性文件起了个别名，可以随意输入

### 4. 运行项目
```bash
cd /home/zy/github2025/2025-/week1-简易学生成绩管理系统
./sms
```
先进入到刚才可执行文件所在的文件夹，再使用`./`指令启动刚在编译得到的可执行文件，后面的文件名sms则是根据自己所取的名字为准

---

## 使用方法
运行程序后，会显示下列主菜单：
```bash
学生成绩管理系统
1. 添加学生信息
2. 查询学生信息
3. 修改学生信息
4. 删除学生信息
5. 显示所有学生信息
6. 统计功能
7. 保存到文件
8. 从文件加载
0. 退出
请输入您的选择: 
```
根据所提示的内容输入你想进行的操作（0～8）

## 项目截图
![alt text](<2025-02-05 21-42-32 的屏幕截图.png>)
![alt text](<2025-02-05 22-32-35 的屏幕截图.png>)
