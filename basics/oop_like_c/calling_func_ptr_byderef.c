#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int experience;
    double basic_salary;
    double salary;
    char name[20];
    double (*calculate_salary) (struct employee* emp, int exp);    //function pointer to accept calc_salary_exp
} employee ;

// pass into the function pointer (calculates the salary by basic_salary, experience) 
double cal_salary_exp(employee* emp, int exp){
    emp->salary = emp->basic_salary;
    if(exp>15)
        emp->salary +=25000;
    else if (exp>10)
        emp->salary +=15000;
    else if(exp>5)
        emp->salary +=5000;
}

//calling function pointer using dereference operator
employee* new_employee(char* name, int exp, double basic_salary){
    employee* obj = (employee*) malloc(sizeof(employee));
    strcpy(obj->name,name);
    obj->basic_salary = basic_salary;
    obj->experience = exp;
    obj->calculate_salary = &cal_salary_exp;    //only assignment
    (*obj->calculate_salary)(obj, exp);         //executes function ptr
    return obj;
}

void print_employee(employee* e){
    printf("-----------------\n");
    printf("name:%s\n",e->name);
    printf("basic salary:%lf\n", e->basic_salary);
    printf("experience:%d\n", e->experience);
    printf("current salary:%lf\n", e->salary);
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