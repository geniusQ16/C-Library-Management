#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#define N 1000
#define LEN sizeof(book)
 
typedef struct book
{
	int num;							//编号 
	char name[31];						//书名 
	char author_name[27];				//作者名 
	char chubanshe[20];					//出版社 
	int jieyucishu;						//借阅次数 
}book; 
 
struct book temp;
struct book temp2;
int  tushuzongshu;
 
int luru();
void chaxun();
int shanchu();
void xiugai();
void chaxuncishu();
void tongji();

int main(void)
{	
	int n;
	Sleep(300);
	loop1:
	tongji();	
	printf("\n\n\t\t********************************图书管理系统**************************************");
	printf("\n\n\n\t\t\t*********欢迎使用图书馆管理系统，请选择你需要的操作**********");
	printf("\n\n\n\n当前图书馆藏书一共有%d本。",tushuzongshu);
	printf("\n\n\n\t\t\t\t\t\t1.图书录入系统");
	printf("\n\n\n\t\t\t\t\t\t2.图书查询系统");
	printf("\n\n\n\t\t\t\t\t\t3.图书删除系统");
	printf("\n\n\n\t\t\t\t\t\t4.图书修改系统");
	printf("\n\n\n\t\t\t\t\t\t5.图书借阅次数最值系统");
	printf("\n\n\n\t\t\t\t\t\t6.退出图书管理系统");
	printf("\n\n\n\t\t\t\t\t\t请选择您所需要的操作：    ");
	scanf("%d",&n);
	if(n>=1&&n<=5){
		system("ClS");
	} 
	else if(n==6){
		system("ClS");
		printf("再次按下回车键退出，谢谢使用！");
	}
	else{
		system("CLS");
		goto loop1;
	}
	switch(n)
	{
		case 1:luru();goto loop1;
		case 2:chaxun();goto loop1;
		case 3:shanchu();goto loop1;
		case 4:xiugai();goto loop1;
		case 5:chaxuncishu();goto loop1;
	}
    return 0;
}
 
int luru()
{	
	FILE *fp=NULL;
	book stu;
    book check;
	char flag = 'y';
	fp=fopen("book1.dat","ab+");
	
	while((flag == 'y'||flag == 'Y')){
		printf("\n\n\n\n\t\t\t\t****************这里是图书录入系统*******************");
		printf("\n请输入图书id: ");
		scanf("%d",&stu.num);
        
        int duplicate = 0;

        rewind(fp);
        while (fread(&check, sizeof(book), 1, fp) == 1) {
            if (check.num == stu.num) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("\n该图书编号已存在，请重新输入！\n");
            continue;
        }

        fseek(fp, 0, SEEK_END);

		printf("\n请输入图书书名: ");
		scanf("%s",stu.name);
		printf("\n请输入图书作者: ");
		scanf("%s",stu.author_name);
		printf("\n请输入图书出版社: ");
		scanf("%s",stu.chubanshe);
		stu.jieyucishu=0;
		
		fwrite(&stu,LEN,1,fp);
		fflush(stdin);
		
		printf("\n\n\n是否继续输入？继续请输入y或n：");
		scanf("%c",&flag); 
	}
	system("CLS");
	fclose(fp);
	return 0;
	
} 
 
void chaxun()
{
	FILE *fp=NULL;
	book stu;
	int n,j,t=-1;
	int nums;
	char name[N],authors_name[40],chubanshe1[40];
	loop3:
	fp = fopen("book1.dat","rb+");
    	if (fp == NULL)
{
    printf("无法打开图书数据文件！\n");
    return;
}	
	printf("\n\n\n\n\t\t\t\t****************这里是图书查询系统*******************");
	printf("\n\t\t\t\t\t请选择你所查询的方式:");
	printf("\n\n\t\t\t\t\t1.编号查询；");
	printf("\n\n\t\t\t\t\t2.书名查询；"); 
	printf("\n\n\t\t\t\t\t3.作者查询；"); 
	printf("\n\n\t\t\t\t\t4.出版社查询；");
	printf("\n\n\t\t\t\t\t5.返回主菜单；");
	printf("请输入您的选择：");
	scanf("%d",&n);
	system("CLS");
	if(n==1){
		printf("\n\t\t\t\t\t\t请您输入图书编号：");
		scanf("%d",&nums);
		fseek(fp,0,SEEK_SET);
		while(fread(&stu,LEN,1,fp)){
			if(nums==stu.num)
			{
				t=1;
				printf("\n\t\t\t\t\t此书为%s,借阅数为%d,是否选择借阅?1.是   2.否",stu.name,stu.jieyucishu);
				printf("\n请输入你的选择:");
				scanf("%d",&j);
				if(j==1){
					stu.jieyucishu++;
					fseek(fp,-4,SEEK_CUR);
					fwrite(&stu.jieyucishu,sizeof(int),1,fp);
					printf("\n借阅成功！请从管理员处领取书籍。3秒钟后返回主菜单");
					t=-1;
					fclose(fp);
					Sleep(3000); 
					system("CLS");
					goto loop3;
				}
				else{
					printf("\n3秒钟后返回主菜单");
					t=-1;
					fclose(fp);
					Sleep(3000);
					system("CLS");
					goto loop3;
				} 
			}
		}
		fclose(fp);
		if(t==-1){
			printf("未找到您所需要的书籍，3秒后返回上一界面。");
			Sleep(3000);
			system("CLS");
			goto loop3;
		}
	}
 
	else if(n==2){
		printf("\n\t\t\t\t\t请输入书名：");
		scanf("%999s",name);
		fseek(fp,0,SEEK_SET);
		while(fread(&stu,LEN,1,fp)){
			if(strcmp(name,stu.name) == 0)
			{
				t=1;
				printf("\n\t\t\t\t\t此书为%s,借阅数为%d,是否选择借阅?1.是   2.否",stu.name,stu.jieyucishu);
				printf("\n请输入你的选择:");
				scanf("%d",&j);
				if(j==1){
					stu.jieyucishu++;
					fseek(fp,-4,SEEK_CUR);
					fwrite(&stu.jieyucishu,sizeof(int),1,fp);
					printf("\n借阅成功！请从管理员处领取书籍。3秒钟后返回主菜单");
					t=-1;
					fclose(fp);
					Sleep(3000);
					system("CLS"); 
					goto loop3;
				}
				else{
					printf("\n3秒钟后返回主菜单");
					t=-1;
					fclose(fp);
					Sleep(3000);
					system("CLS");
					goto loop3;
				}				
			}
		}
		fclose(fp);
		if(t==-1){
			printf("未找到您所需要的书籍，3秒后返回上一界面。");
			Sleep(3000);
			system("CLS");
			goto loop3;
		}
	
	}
 
	else if(n==3){
		printf("\n\t\t\t\t\t请输入书作者：");
		scanf("%39s",authors_name);
		fseek(fp,0,SEEK_SET);
		while(fread(&stu,LEN,1,fp)){
			if(strcmp(authors_name,stu.author_name) == 0){
				printf("\n\t\t\t\t\t作者的图书有%s\n",stu.name);
			}
			t=1;
		}
		fclose(fp);
		if(t==-1){
			printf("\n\t\t\t\t\t未找到您所需要的书籍，3秒后返回上一界面。");
			Sleep(3000);
			system("CLS");
			goto loop3;
		}
		else if(t!=-1){
			printf("\n\t\t\t\t\t是否返回主菜单？1.是  2.否");
			t=-1;
			scanf("%d",&j);
			if(j==1){
				printf("\n\t\t\t\t\t3秒钟后返回主菜单");
				Sleep(3000);
				system("CLS"); 
			}
			else{
				printf("\n\t\t\t\t\t3秒钟后返回主菜单");
				Sleep(3000);
				system("CLS");
			} 
		}
	}
	else if(n==4){
		printf("\n\t\t\t\t\t请输入书出版社：");
		scanf("%39s",chubanshe1);
		fseek(fp,0,SEEK_SET);
		while(fread(&stu,LEN,1,fp)){
			if(strcmp(chubanshe1,stu.chubanshe) == 0){
				printf("\n\t\t\t\t\t出版社的图书有%s\n",stu.name);
			}
			t=1;
		}		
		fclose(fp);
		if(t==-1){
			printf("\t\t\t\t\t未找到您所需要的书籍，3秒后返回上一界面。");
			Sleep(3000);
			goto loop3;
		}
		else if(t!=-1){
			printf("\n\t\t\t\t\t是否返回主菜单？1.是  2.否");
			scanf("%d",&j);
			if(j==1){
				printf("\n\t\t\t\t\t3秒钟后返回主菜单");
				Sleep(3000);
				system("CLS"); 
			}
			else{
				printf("\n\t\t\t\t\t3秒钟后返回主菜单");
				Sleep(3000);
				system("CLS");
			} 
		}
	}
	else if(n==5){
		printf("\n\t\t\t\t\t3秒钟后返回主菜单");
		Sleep(3000);
		system("CLS");
	} 
}
 

int shanchu()
{
    int n, j;
    int nums;
    int found;
    book stu;
    FILE *fp, *fp1;
    char name[20], authors_name[40], chubanshe1[40];

    while (1) {
        printf("\n\n****************这里是图书删除系统****************\n");
        printf("1. 按书籍编号删除\n");
        printf("2. 按书籍书名删除\n");
        printf("3. 按书籍作者查询\n");
        printf("4. 按出版社查询\n");
        printf("5. 返回主菜单\n");
        printf("请输入您的选择：");

        if (scanf("%d", &n) != 1) {
            printf("输入无效！\n");
            while (getchar() != '\n');
            continue;
        }

        if (n == 5) {
            return 0;
        }

        if (n < 1 || n > 5) {
            printf("选择无效，请重新输入。\n");
            continue;
        }

        fp = fopen("book1.dat", "rb");
        if (fp == NULL) {
            perror("打开图书文件失败");
            return -1;
        }

        if (n == 1) {
            printf("请输入书籍编号：");
            if (scanf("%d", &nums) != 1) {
                fclose(fp);
                printf("编号输入无效！\n");
                while (getchar() != '\n');
                continue;
            }
        } else if (n == 2) {
            printf("请输入书籍名称：");
            scanf("%19s", name);
        } else if (n == 3) {
            printf("请输入书籍作者：");
            scanf("%39s", authors_name);
        } else {
            printf("请输入书籍出版社：");
            scanf("%39s", chubanshe1);
        }

        found = 0;

        if (n == 1 || n == 2) {
            while (fread(&stu, LEN, 1, fp) == 1) {
                if ((n == 1 && stu.num == nums) ||
                    (n == 2 && strcmp(name, stu.name) == 0)) {
                    found = 1;
                    printf("找到图书：编号 %d，书名 %s\n",
                           stu.num, stu.name);
                    break;
                }
            }

            if (!found) {
                fclose(fp);
                printf("未找到该图书。\n");
                continue;
            }

            printf("确认删除？1.是  2.否：");
            if (scanf("%d", &j) != 1 || j != 1) {
                fclose(fp);
                printf("已取消删除。\n");
                continue;
            }

            fp1 = fopen("linshi.dat", "wb");
            if (fp1 == NULL) {
                fclose(fp);
                perror("创建临时文件失败");
                return -1;
            }

            rewind(fp);
            while (fread(&stu, LEN, 1, fp) == 1) {
                if ((n == 1 && stu.num == nums) ||
                    (n == 2 && strcmp(name, stu.name) == 0)) {
                    continue;
                }

                if (fwrite(&stu, LEN, 1, fp1) != 1) {
                    fclose(fp);
                    fclose(fp1);
                    remove("linshi.dat");
                    printf("写入临时文件失败，原文件未主动删除。\n");
                    return -1;
                }
            }

            if (ferror(fp) || fclose(fp) != 0) {
                fclose(fp1);
                remove("linshi.dat");
                printf("读取原文件失败，取消替换。\n");
                return -1;
            }

            if (fclose(fp1) != 0) {
                remove("linshi.dat");
                printf("临时文件保存失败。\n");
                return -1;
            }

            if (remove("book1.dat") != 0) {
                perror("删除原文件失败");
                remove("linshi.dat");
                return -1;
            }

            if (rename("linshi.dat", "book1.dat") != 0) {
                perror("替换图书文件失败");
                printf("请保留 linshi.dat，勿继续录入或删除。\n");
                return -1;
            }

            printf("删除完成，请重新查询确认。\n");
        } else {
            while (fread(&stu, LEN, 1, fp) == 1) {
                if ((n == 3 &&
                     strcmp(authors_name, stu.author_name) == 0) ||
                    (n == 4 &&
                     strcmp(chubanshe1, stu.chubanshe) == 0)) {
                    printf("编号：%d，书名：%s\n", stu.num, stu.name);
                    found = 1;
                }
            }

            fclose(fp);

            if (!found) {
                printf("未找到匹配的图书。\n");
            }
        }
    }
}

 


void xiugai()
{
    book stu;
    FILE *fp;
    int n, target_num, found;
    char new_name[N];
    char new_author[40];
    char new_chubanshe[40];

    while (1)
    {
        printf("\n\n\t\t\t****************图书修改系统****************");
        printf("\n\t\t\t1. 修改图书编号");
        printf("\n\t\t\t2. 修改图书书名");
        printf("\n\t\t\t3. 修改图书作者");
        printf("\n\t\t\t4. 修改图书出版社");
        printf("\n\t\t\t5. 返回主菜单");
        printf("\n\t\t\t请输入您的选择：");

        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n');
            printf("输入无效，请输入数字！\n");
            continue;
        }

        if (n == 5)
        {
            system("CLS");
            return;
        }

        if (n < 1 || n > 4)
        {
            printf("选择无效，请重新输入！\n");
            continue;
        }

        fp = fopen("book1.dat", "rb+");
        if (fp == NULL) {
    printf("无法打开图书数据文件！\n");
    return;
}
        if (fp == NULL)
        {
            printf("无法打开图书数据文件！\n");
            return;
        }

        printf("请输入要修改的图书当前编号：");
        if (scanf("%d", &target_num) != 1)
        {
            while (getchar() != '\n');
            fclose(fp);
            printf("编号输入无效！\n");
            continue;
        }

        found = 0;

        while (fread(&stu, sizeof(stu), 1, fp) == 1)
        {
            if (stu.num == target_num)
            {
                found = 1;

                if (n == 1)
                {
                    int new_num;
                    int duplicate = 0;
                    book check;

                    printf("请输入新的图书编号：");
                    scanf("%d", &new_num);

                    if (new_num != target_num)
                    {
                        FILE *check_fp = fopen("book1.dat", "rb");

                        if (check_fp != NULL)
                        {
                            while (fread(&check, sizeof(check), 1, check_fp) == 1)
                            {
                                if (check.num == new_num)
                                {
                                    duplicate = 1;
                                    break;
                                }
                            }
                            fclose(check_fp);
                        }
                    }

                    if (duplicate)
                    {
                        printf("该图书编号已存在，修改失败！\n");
                        break;
                    }

                    stu.num = new_num;
                }
                else if (n == 2)
                {
                    printf("请输入新的图书书名：");
                    scanf("%s", new_name);
                    strcpy(stu.name, new_name);
                }
                else if (n == 3)
                {
                    printf("请输入新的图书作者：");
                    scanf("%s", new_author);
                    strcpy(stu.author_name, new_author);
                }
                else if (n == 4)
                {
                    printf("请输入新的图书出版社：");
                    scanf("%s", new_chubanshe);
                    strcpy(stu.chubanshe, new_chubanshe);
                }

                if (n == 1 && stu.num == target_num)
                {
                    break;
                }

                if (n == 1 || n == 2 || n == 3 || n == 4)
                {
                    fseek(fp, -(long)sizeof(stu), SEEK_CUR);

                    if (fwrite(&stu, sizeof(stu), 1, fp) == 1)
                    {
                        fflush(fp);
                        printf("图书信息修改成功！\n");
                    }
                    else
                    {
                        printf("图书信息写入失败！\n");
                    }
                }

                break;
            }
        }

        if (!found)
        {
            printf("未找到该图书编号，修改失败！\n");
        }

        fclose(fp);
        printf("按回车键继续...");
        while (getchar() != '\n');
        getchar();
        system("CLS");
    }
}

 
void chaxuncishu()
{
	FILE *fp;
	book stu;
	int min=10000,max=0,m;
	loop7: 
	fp = fopen("book1.dat","rb+");
	fseek(fp, 0, SEEK_SET);
	while (fread(&stu,LEN,1,fp)){
		if(stu.jieyucishu>=max){
			max=stu.jieyucishu;
			strcpy(temp.name,stu.name);	
		}
		if(stu.jieyucishu<=min&&stu.jieyucishu>=0){
			min=stu.jieyucishu;
			strcpy(temp2.name,stu.name);
		}
	}
	fclose(fp);
	printf("\n\n\t\t******************这里是图书借阅次数最值界面*********************"); 
	printf("\n\n\t\t******************图书借阅次数最多的图书为:%s,借阅次数为:%d********************",temp.name,max);
	printf("\n\n\t\t******************图书借阅次数最少的图书为:%s,借阅次数为:%d********************",temp2.name,min);
	printf("\n\n\t\t******************是否返回主菜单？1.是 2.否********************");
	scanf("%d",&m);
	if(m==1){
		printf("\n\n\t\t******************3秒后返回主菜单。***********************");
		Sleep(3000);
		system("CLS");
	}
	else if(m==2){
		system("CLS");
		goto loop7;
	}			
}
 

void tongji()
{
    FILE *fp;
    book stu;

    tushuzongshu = 0;

    fp = fopen("book1.dat", "rb");

    /* 文件不存在时，按空图书馆处理 */
    if (fp == NULL)
    {
        return;
    }

    while (fread(&stu, sizeof(book), 1, fp) == 1)
    {
        tushuzongshu++;
    }

    fclose(fp);
}
