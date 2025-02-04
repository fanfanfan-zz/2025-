#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 80 /*设置最大学生容量不超过80*/
#define MAX_NAME_LENGTH 50 /*设置学生名字的最长长度*/
#define MAX_COURSES 8 /*设置每个学生的课程数量不超过8门*/

// 创建学生结构体
typedef struct {
    int id;                      // 学号
    char name[MAX_NAME_LENGTH];  // 姓名
    float scores[MAX_COURSES];   // 课程成绩
    int course_count;            // 课程数量
    float average_score;         // 平均成绩
    int rank;                    // 排名
} Student;

Student students[MAX_STUDENTS];  // 学生数组
int student_count = 0;           // 当前学生数量

// 计算某个学生的平均成绩
float calculate_average_score(Student* student) {
    float total_score = 0;
    for (int i = 0; i < student->course_count; i++) {
        total_score += student->scores[i];
    }
    return total_score / student->course_count;
}

// 按平均成绩排序（从高到低）
void sort_students_by_average_score() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (students[j].average_score < students[j + 1].average_score) {
                // 交换两个学生的位置
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 设置学生的排名（支持并列排名）
void set_student_ranks() {
    for (int i = 0; i < student_count; i++) {
        if (i == 0) {
            students[i].rank = 1;  // 第一名
        }
        else {
            if (students[i].average_score == students[i - 1].average_score) {
                // 如果平均成绩相同，则排名并列
                students[i].rank = students[i - 1].rank;
            }
            else {
                // 否则排名为当前索引 + 1
                students[i].rank = i + 1;
            }
        }
    }
}

// 添加学生信息
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("学生数量已达到上限，无法添加更多学生，请联系管理员修改最大学生容量。\n");
        return;
    }

    Student new_student;
    printf("请输入学号: ");
    scanf("%d", &new_student.id);

    // 检查学号是否重复
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == new_student.id) {
            printf("学号重复，请重新输入。\n");
            return;
        }
    }

    // 输入学生姓名
    printf("请输入姓名: ");
    scanf("%s", new_student.name);

    // 输入课程数量
    printf("请输入课程数量 (1到%d): ", MAX_COURSES);
    scanf("%d", &new_student.course_count);
    if (new_student.course_count < 1 || new_student.course_count > MAX_COURSES) {
        printf("课程数量无效，请输入1到%d之间的数字。\n", MAX_COURSES);
        return;
    }

    // 输入课程成绩
    for (int i = 0; i < new_student.course_count; i++) {
        printf("请输入第 %d 门课程的成绩 (0到100): ", i + 1);
        scanf("%f", &new_student.scores[i]);
        if (new_student.scores[i] < 0 || new_student.scores[i] > 100) {
            printf("成绩无效，必须在0到100之间。\n");
            return;
        }
    }

    students[student_count++] = new_student;
    printf("学生信息添加成功！\n");
}

//通过姓名或者学号查询学生
void inquire_student() {
    int choice;
    printf("选择查询方式:\n");
    printf("1. 根据学号查询\n");
    printf("2. 根据姓名查询\n");
    printf("请输入您的选择 (1或2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("请输入要查询的学号: ");
        scanf("%d", &id);

        for (int i = 0; i < student_count; i++) {
            if (students[i].id == id) {
                printf("学号: %d, 姓名: %s, 成绩: ", students[i].id, students[i].name);
                for (int j = 0; j < students[i].course_count; j++) {
                    printf("%.2f ", students[i].scores[j]);
                }
                printf("\n");
                return;
            }
        }

        printf("未找到该学生信息。\n");
    }
    else if (choice == 2) {
        char name[MAX_NAME_LENGTH];
        printf("请输入要查询的姓名: ");
        scanf("%s", name);

        int found = 0;  // 用于标记是否找到学生  
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].name, name) == 0) {
                printf("学号: %d, 姓名: %s, 成绩: ", students[i].id, students[i].name);
                for (int j = 0; j < students[i].course_count; j++) {
                    printf("%.2f ", students[i].scores[j]);
                }
                printf("\n");
                found = 1; // 找到学生，标记  
            }
        }

        if (!found) {
            printf("未找到该学生信息。\n");
        }
    }
    else {
        printf("无效的选择，请重新输入。\n");
    }
}

// 修改学生信息
void modify_student() {
    int id;
    printf("请输入要修改的学号: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("请输入新的姓名: ");
            scanf("%s", students[i].name);

            printf("请输入新的课程数量 (1到%d): ", MAX_COURSES);
            scanf("%d", &students[i].course_count);
            if (students[i].course_count < 1 || students[i].course_count > MAX_COURSES) {
                printf("课程数量无效，请输入1到%d之间的数字。\n", MAX_COURSES);
                return;
            }

            for (int j = 0; j < students[i].course_count; j++) {
                printf("请输入第 %d 门课程的新成绩 (0到100): ", j + 1);
                scanf("%f", &students[i].scores[j]);
                if (students[i].scores[j] < 0 || students[i].scores[j] > 100) {
                    printf("成绩无效，必须在0到100之间。\n");
                    return;
                }
            }

            printf("学生信息修改成功！\n");
            return;
        }
    }

    printf("未找到该学生信息。\n");
}

// 删除学生信息
void delete_student() {
    int id;
    printf("请输入要删除的学号: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            // 将最后一个学生信息移动到被删除的位置
            students[i] = students[student_count - 1];
            student_count--;
            printf("学生信息删除成功！\n");
            return;
        }
    }

    printf("未找到该学生信息。\n");
}

// 显示所有学生信息（按平均成绩排序）
void list_students() {
    //检查学生数量是否为0
    if (student_count == 0) {
        printf("没有学生信息可显示。\n");
        return;
    }

    // 计算每个学生的平均成绩
    for (int i = 0; i < student_count; i++) {
        students[i].average_score = calculate_average_score(&students[i]);
    }

    // 按平均成绩排序（调用函数sort_students_by_average_score）
    sort_students_by_average_score();

    // 设置学生的排名（调用函数set_student_ranks）
    set_student_ranks();

    // 打印学生信息
    for (int i = 0; i < student_count; i++) {
        printf("排名: %d, 学号: %d, 姓名: %s, 成绩: [", students[i].rank, students[i].id, students[i].name);
        for (int j = 0; j < students[i].course_count; j++) {
            printf("课程%d: %.2f", j + 1, students[i].scores[j]);
            if (j < students[i].course_count - 1) {
                printf(", ");
            }
        }
        printf("], 平均成绩: %.2f\n", students[i].average_score);
    }
}

// 统计功能（计算全班最高分，最低分，班级平均成绩）
void statistics() {
    if (student_count == 0) {
        printf("没有学生信息可统计。\n");
        return;
    }

    float total = 0;
    float max_score = -1; /*用于存储最高成绩*/
    float min_score = 101; /*用于存储最低成绩*/

    for (int i = 0; i < student_count; i++) {
        for (int j = 0; j < students[i].course_count; j++) {
            total += students[i].scores[j];
            if (students[i].scores[j] > max_score) {
                max_score = students[i].scores[j];
            }
            if (students[i].scores[j] < min_score) {
                min_score = students[i].scores[j];
            }
        }
    }

    float average = total / (student_count * students[0].course_count);
    printf("全班平均成绩: %.2f\n", average);
    printf("全班最高分: %.2f\n", max_score);
    printf("全班最低分: %.2f\n", min_score);
}
// 保存学生信息到文件
void save_to_file() {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("文件打开失败！\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d %s %d ", students[i].id, students[i].name, students[i].course_count);
        for (int j = 0; j < students[i].course_count; j++) {
            fprintf(file, "%.2f ", students[i].scores[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("学生信息已保存到文件。\n");
}

// 从文件加载学生信息
void load_from_file() {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("文件打开失败！\n");
        return;
    }

    student_count = 0;
    while (fscanf(file, "%d %s %d", &students[student_count].id, students[student_count].name, &students[student_count].course_count) != EOF) {
        for (int j = 0; j < students[student_count].course_count; j++) {
            fscanf(file, "%f", &students[student_count].scores[j]);
        }
        student_count++;
    }

    fclose(file);
    printf("学生信息已从文件加载。\n");
}

// 主菜单
void menu() {
    int choice;
    while (1) {
        printf("\n学生成绩管理系统\n");
        printf("1. 添加学生信息\n");
        printf("2. 查询学生信息\n");
        printf("3. 修改学生信息\n");
        printf("4. 删除学生信息\n");
        printf("5. 显示所有学生信息\n");
        printf("6. 统计功能\n");
        printf("7. 保存到文件\n");
        printf("8. 从文件加载\n");
        printf("0. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: add_student(); break;
        case 2: inquire_student(); break;
        case 3: modify_student(); break;
        case 4: delete_student(); break;
        case 5: list_students(); break;
        case 6: statistics(); break;
        case 7: save_to_file(); break;
        case 8: load_from_file(); break;
        case 0: exit(0);
        default: printf("无效的选择，请重新输入。\n");
        }
    }
}

int main() {
    menu();
    return 0;
}