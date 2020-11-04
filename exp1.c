#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stu{
    int id;
    int* score;
    char name[20];
};
int id(struct stu a,struct stu b){
    return a.id<b.id;
}
int score(struct stu a,struct stu b){
    return a.score[0]<b.score[0];
}
int name(struct stu a,struct stu b){
    return (strcmp(a.name,b.name)<0);
}
void scan(int *a){
    while(scanf("%d", a)!=1){
        printf("Invaid input!\n");
        while(getchar()!='\n');
    }
}
void getname(char* s){
    while(getchar()!='\n');
    fgets(s,19,stdin);
    strtok(s,"\n");
}
struct stu* input(int n,int n1,int* score){
    struct stu* p=malloc(n*sizeof(struct stu));
    for(int i=0;i<n;i++){
        printf("Please input student id:");
        scan(&(p[i].id));
        printf("Please input student name:");
        getname(&(p[i].name));
        printf("Please input student score:");
        p[i].score=score+i*(n1+1);
        p[i].score[0]=0;
        for(int j=1;j<=n1;j++){
            do{
                scan(&(p[i].score[j]));
            }while(p[i].score[j]>100||p[i].score[j]<0);
            p[i].score[0]+=p[i].score[j];
        }
    }
    return p;
}
int sum(struct stu* p,int n,int s){
    int ret=0;
    n--;
    while(n!=-1){
        ret+=p[n].score[s];
        n--;
    }
    return ret;
}
int* index_sort(struct stu* s,int n,int (*cmp)(struct stu a,struct stu b)){
    int t;
    int *index;
    index=malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        index[i]=i;
    }
    for(int i=n/2;i!=-1;i--){
        adjust(s,index,i,n-1,cmp);
    }
    for(int j=n-1;j!=0;j--){
        t=index[j];
        index[j]=index[0];
        index[0]=t;
        adjust(s,index,0,j-1,cmp);
    }
    
    return index;
}
void adjust(struct stu* s,int index[],int i,int max,int (*cmp)(struct stu a,struct stu b)){
    int left=i*2+1,right=i*2+2,t;
    while(left<=max){
        if(right>max){
            if(cmp(s[index[i]],s[index[left]])){
                    t=index[left];
                    index[left]=index[i];
                    index[i]=t;
                    break;
            }
            break;
        }
        if(cmp(s[index[left]],s[index[right]])&&cmp(s[index[i]],s[index[right]])){
            t=index[right];
            index[right]=index[i];
            index[i]=t;
            i=right;
        }else if(cmp(s[index[i]],s[index[left]])){
            t=index[left];
            index[left]=index[i];
            index[i]=t;
            i=left;
        }else{
            break;
        }
        left=i*2+1;
        right=i*2+2;
    }
}
void statistic(struct stu* p,int n,int k){
    int r[5],s;
    memset(r,0,sizeof(int)*5);
    for(int i=0;i<n;i++){
        s=p[i].score[k];
        if(s>99){
            r[4]++;
        }else if(s<60){
            r[0]++;
        }else{
            r[s/10-5]++;
        }
    }
    printf("youxiu\t%d\t%.1f%%\n",r[4],r[4]*100.0/n);
    printf("lianghao\t%d\t%.1f%%\n",r[3],r[3]*100.0/n);
    printf("zhongdeng\t%d\t%.1f%%\n",r[2],r[2]*100.0/n);
    printf("jige\t%d\t%.1f%%\n",r[1],r[1]*100.0/n);
    printf("bujige\t%d\t%.1f%%\n",r[0],r[0]*100.0/n);
}
void query(struct stu* p,int* index_score,int id,int n,int n1){
    int score=-1;
    for(int i=0;i<n;i++){
        if(p[i].id==id){
            score=p[i].score[0];
        }
    }
    if(score==-1){
        printf("Not Found\n");
    }else{
        for(int i=0;;i++){
            if(p[index_score[i]].score[0]==score){
                printf("%d\t",n-i);
                for(int j=1;j<=n1;j++){
                    printf("%d\t",p[index_score[i]].score[j]);
                }
                printf("\n");
                break;
            }
        }
    }
}
void query_name(struct stu* p,int* index_score,char name[20],int n,int n1){
    int score=-1;
    for(int i=0;i<n;i++){
        if(strcmp(p[i].name,name)==0){
            score=p[i].score[0];
        }
    }
    if(score==-1){
        printf("Not Found\n");
    }else{
        for(int i=0;;i++){
            if(p[index_score[i]].score[0]==score){
                printf("%s\t%d\t",name,n-i);
                for(int j=1;j<=n1;j++){
                    printf("%d\t",p[index_score[i]].score[j]);
                }
                printf("\n");
                break;
            }
        }
    }
}
int main(){
    printf("student NO. 200110924\n");
    printf("subject No.5 - Program No.1\n");
    int a,n,m,n1;
    char qname[20];
    struct stu* p=NULL;
    int* index_id=NULL;
    int* index_score=NULL;
    int* index_name=NULL;
    int* s=NULL;
    while(1){
        printf("1.Input record\n");
        printf("2.Calculate total and average score of course\n");
        printf("3.Sort in descending order by score\n");
        printf("4.Sort in ascending order by score\n");
        printf("5.Sort in ascending order by number\n");
        printf("6.Sort in dictionary order by name\n");
        printf("7.Search by number\n");
        printf("8.Search by name\n");
        printf("9.Statistic analysis!\n");
        printf("10.List Record\n");
        printf("11.Exit\n");
        do{
            scan(&a);
        }while(a<1||a>11);
        if(a==11)return 0;
        if(a==1){
            if(p!=NULL)free(p);
            if(index_id!=NULL)free(index_id);
            if(index_score!=NULL)free(index_score);
            if(index_name!=NULL)free(index_name);
            if(s!=NULL)free(s);
            printf("Please input the number of students:\n");
            scan(&n);
            printf("Please input the number of subjects:\n");
            scan(&n1);
            s=malloc(n*(n1+1)*sizeof(int));
            p=input(n,n1,s);
            index_id=index_sort(p,n,id);
            index_score=index_sort(p,n,score);
            index_name=index_sort(p,n,name);
        }else if(p!=NULL){
            switch(a){
                case 2:
                    for(int i=1;i<=n1;i++){
                        printf("%d\t",sum(p,n,i));
                    }
                    printf("\n");
                    for(int i=1;i<=n1;i++){
                        printf("%f\t",sum(p,n,i)*1.0/n);
                    }
                    printf("\n");
                    break;
                case 3:
                    printf("Student ID\tName\tScore\n");
                    for(int i=n-1;i!=-1;i--){
                        printf("%d\t%s\t",p[index_score[i]].id,p[index_score[i]].name);
                        for(int j=1;j<=n1;j++){
                            printf("%d\t",p[index_score[i]].score[j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    break;
                case 4:
                    printf("Student ID\tName\tScore\n");
                    for(int i=0;i!=n;i++){
                        printf("%d\t%s\t",p[index_score[i]].id,p[index_score[i]].name);
                        for(int j=1;j<=n1;j++){
                            printf("%d\t",p[index_score[i]].score[j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    break;
                case 5:
                    printf("Student ID\tName\tScore\n");
                    for(int i=0;i!=n;i++){
                        printf("%d\t%s\t",p[index_id[i]].id,p[index_id[i]].name);
                        for(int j=1;j<=n1;j++){
                            printf("%d\t",p[index_id[i]].score[j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    break;
                case 6:
                    printf("Student ID\tName\tScore\n");
                    for(int i=0;i!=n;i++){
                        printf("%d\t%s\t",p[index_name[i]].id,p[index_name[i]].name);
                        for(int j=1;j<=n1;j++){
                            printf("%d\t",p[index_name[i]].score[j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    break;
                case 7:
                    scan(&m);
                    query(p,index_score,m,n,n1);
                    break;
                case 8:
                    getname(qname);
                    query_name(p,index_score,qname,n,n1);
                    break;
                case 9:
                    for(int i=1;i<=n1;i++){
                        statistic(p,n,i);
                    }
                    break;
                case 10:
                    printf("Student ID\tName\tScore\n");
                    for(int i=0;i<n;i++){
                        printf("%d\t%s\t",p[i].id,p[i].name);
                        for(int j=1;j<=n1;j++){
                            printf("%d\t",p[i].score[j]);
                        }
                        printf("%d\t%f\t\n",p[i].score[0],p[i].score[0]*1.0/n1);
                    }
                    break;
            }
        }
    }
}
