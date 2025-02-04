#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 80 /*�������ѧ������������80*/
#define MAX_NAME_LENGTH 50 /*����ѧ�����ֵ������*/
#define MAX_COURSES 8 /*����ÿ��ѧ���Ŀγ�����������8��*/

// ����ѧ���ṹ��
typedef struct {
    int id;                      // ѧ��
    char name[MAX_NAME_LENGTH];  // ����
    float scores[MAX_COURSES];   // �γ̳ɼ�
    int course_count;            // �γ�����
    float average_score;         // ƽ���ɼ�
    int rank;                    // ����
} Student;

Student students[MAX_STUDENTS];  // ѧ������
int student_count = 0;           // ��ǰѧ������

// ����ĳ��ѧ����ƽ���ɼ�
float calculate_average_score(Student* student) {
    float total_score = 0;
    for (int i = 0; i < student->course_count; i++) {
        total_score += student->scores[i];
    }
    return total_score / student->course_count;
}

// ��ƽ���ɼ����򣨴Ӹߵ��ͣ�
void sort_students_by_average_score() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (students[j].average_score < students[j + 1].average_score) {
                // ��������ѧ����λ��
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// ����ѧ����������֧�ֲ���������
void set_student_ranks() {
    for (int i = 0; i < student_count; i++) {
        if (i == 0) {
            students[i].rank = 1;  // ��һ��
        }
        else {
            if (students[i].average_score == students[i - 1].average_score) {
                // ���ƽ���ɼ���ͬ������������
                students[i].rank = students[i - 1].rank;
            }
            else {
                // ��������Ϊ��ǰ���� + 1
                students[i].rank = i + 1;
            }
        }
    }
}

// ���ѧ����Ϣ
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("ѧ�������Ѵﵽ���ޣ��޷���Ӹ���ѧ��������ϵ����Ա�޸����ѧ��������\n");
        return;
    }

    Student new_student;
    printf("������ѧ��: ");
    scanf("%d", &new_student.id);

    // ���ѧ���Ƿ��ظ�
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == new_student.id) {
            printf("ѧ���ظ������������롣\n");
            return;
        }
    }

    // ����ѧ������
    printf("����������: ");
    scanf("%s", new_student.name);

    // ����γ�����
    printf("������γ����� (1��%d): ", MAX_COURSES);
    scanf("%d", &new_student.course_count);
    if (new_student.course_count < 1 || new_student.course_count > MAX_COURSES) {
        printf("�γ�������Ч��������1��%d֮������֡�\n", MAX_COURSES);
        return;
    }

    // ����γ̳ɼ�
    for (int i = 0; i < new_student.course_count; i++) {
        printf("������� %d �ſγ̵ĳɼ� (0��100): ", i + 1);
        scanf("%f", &new_student.scores[i]);
        if (new_student.scores[i] < 0 || new_student.scores[i] > 100) {
            printf("�ɼ���Ч��������0��100֮�䡣\n");
            return;
        }
    }

    students[student_count++] = new_student;
    printf("ѧ����Ϣ��ӳɹ���\n");
}

//ͨ����������ѧ�Ų�ѯѧ��
void inquire_student() {
    int choice;
    printf("ѡ���ѯ��ʽ:\n");
    printf("1. ����ѧ�Ų�ѯ\n");
    printf("2. ����������ѯ\n");
    printf("����������ѡ�� (1��2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("������Ҫ��ѯ��ѧ��: ");
        scanf("%d", &id);

        for (int i = 0; i < student_count; i++) {
            if (students[i].id == id) {
                printf("ѧ��: %d, ����: %s, �ɼ�: ", students[i].id, students[i].name);
                for (int j = 0; j < students[i].course_count; j++) {
                    printf("%.2f ", students[i].scores[j]);
                }
                printf("\n");
                return;
            }
        }

        printf("δ�ҵ���ѧ����Ϣ��\n");
    }
    else if (choice == 2) {
        char name[MAX_NAME_LENGTH];
        printf("������Ҫ��ѯ������: ");
        scanf("%s", name);

        int found = 0;  // ���ڱ���Ƿ��ҵ�ѧ��  
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].name, name) == 0) {
                printf("ѧ��: %d, ����: %s, �ɼ�: ", students[i].id, students[i].name);
                for (int j = 0; j < students[i].course_count; j++) {
                    printf("%.2f ", students[i].scores[j]);
                }
                printf("\n");
                found = 1; // �ҵ�ѧ�������  
            }
        }

        if (!found) {
            printf("δ�ҵ���ѧ����Ϣ��\n");
        }
    }
    else {
        printf("��Ч��ѡ�����������롣\n");
    }
}

// �޸�ѧ����Ϣ
void modify_student() {
    int id;
    printf("������Ҫ�޸ĵ�ѧ��: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("�������µ�����: ");
            scanf("%s", students[i].name);

            printf("�������µĿγ����� (1��%d): ", MAX_COURSES);
            scanf("%d", &students[i].course_count);
            if (students[i].course_count < 1 || students[i].course_count > MAX_COURSES) {
                printf("�γ�������Ч��������1��%d֮������֡�\n", MAX_COURSES);
                return;
            }

            for (int j = 0; j < students[i].course_count; j++) {
                printf("������� %d �ſγ̵��³ɼ� (0��100): ", j + 1);
                scanf("%f", &students[i].scores[j]);
                if (students[i].scores[j] < 0 || students[i].scores[j] > 100) {
                    printf("�ɼ���Ч��������0��100֮�䡣\n");
                    return;
                }
            }

            printf("ѧ����Ϣ�޸ĳɹ���\n");
            return;
        }
    }

    printf("δ�ҵ���ѧ����Ϣ��\n");
}

// ɾ��ѧ����Ϣ
void delete_student() {
    int id;
    printf("������Ҫɾ����ѧ��: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            // �����һ��ѧ����Ϣ�ƶ�����ɾ����λ��
            students[i] = students[student_count - 1];
            student_count--;
            printf("ѧ����Ϣɾ���ɹ���\n");
            return;
        }
    }

    printf("δ�ҵ���ѧ����Ϣ��\n");
}

// ��ʾ����ѧ����Ϣ����ƽ���ɼ�����
void list_students() {
    //���ѧ�������Ƿ�Ϊ0
    if (student_count == 0) {
        printf("û��ѧ����Ϣ����ʾ��\n");
        return;
    }

    // ����ÿ��ѧ����ƽ���ɼ�
    for (int i = 0; i < student_count; i++) {
        students[i].average_score = calculate_average_score(&students[i]);
    }

    // ��ƽ���ɼ����򣨵��ú���sort_students_by_average_score��
    sort_students_by_average_score();

    // ����ѧ�������������ú���set_student_ranks��
    set_student_ranks();

    // ��ӡѧ����Ϣ
    for (int i = 0; i < student_count; i++) {
        printf("����: %d, ѧ��: %d, ����: %s, �ɼ�: [", students[i].rank, students[i].id, students[i].name);
        for (int j = 0; j < students[i].course_count; j++) {
            printf("�γ�%d: %.2f", j + 1, students[i].scores[j]);
            if (j < students[i].course_count - 1) {
                printf(", ");
            }
        }
        printf("], ƽ���ɼ�: %.2f\n", students[i].average_score);
    }
}

// ͳ�ƹ��ܣ�����ȫ����߷֣���ͷ֣��༶ƽ���ɼ���
void statistics() {
    if (student_count == 0) {
        printf("û��ѧ����Ϣ��ͳ�ơ�\n");
        return;
    }

    float total = 0;
    float max_score = -1; /*���ڴ洢��߳ɼ�*/
    float min_score = 101; /*���ڴ洢��ͳɼ�*/

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
    printf("ȫ��ƽ���ɼ�: %.2f\n", average);
    printf("ȫ����߷�: %.2f\n", max_score);
    printf("ȫ����ͷ�: %.2f\n", min_score);
}
// ����ѧ����Ϣ���ļ�
void save_to_file() {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("�ļ���ʧ�ܣ�\n");
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
    printf("ѧ����Ϣ�ѱ��浽�ļ���\n");
}

// ���ļ�����ѧ����Ϣ
void load_from_file() {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("�ļ���ʧ�ܣ�\n");
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
    printf("ѧ����Ϣ�Ѵ��ļ����ء�\n");
}

// ���˵�
void menu() {
    int choice;
    while (1) {
        printf("\nѧ���ɼ�����ϵͳ\n");
        printf("1. ���ѧ����Ϣ\n");
        printf("2. ��ѯѧ����Ϣ\n");
        printf("3. �޸�ѧ����Ϣ\n");
        printf("4. ɾ��ѧ����Ϣ\n");
        printf("5. ��ʾ����ѧ����Ϣ\n");
        printf("6. ͳ�ƹ���\n");
        printf("7. ���浽�ļ�\n");
        printf("8. ���ļ�����\n");
        printf("0. �˳�\n");
        printf("����������ѡ��: ");
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
        default: printf("��Ч��ѡ�����������롣\n");
        }
    }
}

int main() {
    menu();
    return 0;
}