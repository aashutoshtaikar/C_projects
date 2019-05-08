#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int experience;
    int basic_salary;
    int salary;
    char name[20];
    int (*calculate_salary) (int exp);    //function pointer to accept calc_salary_exp
} employee ;

// pass into the function pointer (calculates the salary by basic_salary, experience) 
int cal_salary_exp(int exp){
    int temp = 0;
    if(exp>15)
        temp +=25000;
    else if (exp>10)
        temp +=15000;
    else if(exp>5)
        temp +=5000;
    return temp;
}

//calling function pointer using dereference operator
employee* new_employee(char* name, int exp, double basic_salary){
    employee* obj = (employee*) malloc(sizeof(employee));
    strcpy(obj->name,name);
    obj->basic_salary = basic_salary;
    obj->experience = exp;
    obj->calculate_salary = cal_salary_exp(exp);   //direct function call
    obj->salary = obj->calculate_salary + obj->basic_salary;
    return obj;
}

void print_employee(employee* e){
    printf("-----------------\n");
    printf("name:%s\n",e->name);
    printf("basic salary:%d\n", e->basic_salary);
    printf("experience:%d\n", e->experience);
    printf("current salary:%d\n", e->salary);
}

void destroy_employee(employee* e){
    free(e);
}


int main() {
    employee *emp1 = new_employee("Ash",14, 2000);
    employee *emp2 = new_employee("Bash",7, 1500);

    print_employee(emp1);
    print_employee(emp2);

    destroy_employee(emp1);
    destroy_employee(emp2);
}