// Kill.cpp: implementation of the CKill class.
//
//////////////////////////////////////////////////////////////////////

#include "Kill.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKill::CKill()
{
	memset(chessdata,0,sizeof(chessdata));
	baseaddress = 0;
}

CKill::~CKill()
{

}

Point CKill::BFS(byte path[11][19],Point ptstart)
{
	byte boolpath[11][19] = {0};//���ʱ�� ��ֹתȦ
	Point dection[4] = {{0,1},{-1,0},{0,-1},{1,0}};//�����ĸ�����
    Point pdefau = {-1,-1};//�����ͨ���أ�-1��-1��
	deque<Point> queue;//��������������ö���
	queue.push_back(ptstart);//��������
	int n = 0;//��ֹ��������
	int i = 0,j = 0,k = 0;
	/* ����Ϊͼ�Ĺ����������*/
	while(!queue.empty())
	{
		Point ptemp = queue.front();
        queue.pop_front();
        boolpath[ptemp.x][ptemp.y] = true;
		if(0 != n && path[ptstart.x][ptstart.y] == path[ptemp.x][ptemp.y])//����ҵ���Ŀ��� ֱ�ӷ���
			return ptemp;
		else
		{
			for(i = 0;i<4;i++)//��������Χ4����������
			{
                if(ptemp.x+dection[i].x>=0 && ptemp.x+dection[i].x<11 &&
                     ptemp.y+dection[i].y >=0 && ptemp.y+dection[i].y<19)//�ж��Ƿ�Խ��
                {
					Point temp1 = {ptemp.x+dection[i].x,ptemp.y+dection[i].y};
					if((0 == path[temp1.x][temp1.y]  && false == boolpath[temp1.x][temp1.y])||
							  path[temp1.x][temp1.y] == path[ptstart.x][ptstart.y] &&
							  false == boolpath[temp1.x][temp1.y])//���û���߹�  ���ҿ�����
					{
							  queue.push_back(temp1);//�����
							  boolpath[temp1.x][temp1.y] = true;//�����߹��ĺۼ�
					}
                }
			}               
		}
        n++;
	}
	return pdefau;
}
void CKill::OnKill()
{
     // TODO: �ڴ���ӿؼ�֪ͨ����������

	 const PCHAR gameCaption="QQ��Ϸ - ��������ɫ��";
	 extern int baseadress;
	 LPCVOID pbase=(LPCVOID)this->baseaddress; //�������ݻ�ַ
	 LPVOID  nbuffer=(LPVOID)&chessdata;   //�����������
	 HANDLE processH;
	 DWORD byread;
	 DWORD processid;
	 HWND gameh=::FindWindow(NULL,gameCaption);
	 int num = 5;
	 while(num--)
	 {
		 //��ȡ���ڽ���ID
		 ::GetWindowThreadProcessId(gameh,&processid);
		 //��ָ������
		 processH=::OpenProcess(PROCESS_ALL_ACCESS,false,processid);
		 //��ָ������ �ڴ����� 
		 if(!::ReadProcessMemory(processH,pbase,nbuffer,11*19,&byread))
		 {
			 printf("���ܶ�ȡ�ڴ�����\n");
			 return ;
		 }
    

		  int i = 0,j = 0,k = 0;
		  int x = 22,y = 187;//�̶����ݲ�Ҫ�ı�  �����޷�ʵ�ֵ��
		  int  lparam = 0;//��ʾָ����	

		  //����ÿһ�����ӹ����������
		  for(i = 0;i<11;i++)
		  {
			  for(j = 0;j<19;j++)
			  {
					if(0 != chessdata[i][j])
					{
						 Point ptstart = {i,j},ptend = {0,0};//��Ҫ�ҵ����ӵ���㴫���������� �������Ե�����Ǹ���
						 ptend = this->BFS(chessdata,ptstart);//�����յ�����
						 if(ptend.x != -1 && ptend.y != -1)//����ҵ���
						 {                              
							  /*��������λ���͵�����������Ϣ ����� �þͿ���*/
							  //��ʾָ���ĸ� �̶���ʽ ��Ҫ�Ķ�
							  lparam = ((y+(35*ptstart.x))<<16)+x+31*(ptstart.y);
							  ::SendMessage(gameh,WM_LBUTTONDOWN,0,lparam);//
							  ::SendMessage(gameh,WM_LBUTTONUP,0,lparam);  // 

							  lparam = ((y+(35*ptend.x))<<16)+x+31*(ptend.y);
							  ::SendMessage(gameh,WM_LBUTTONDOWN,0,lparam);//
							  ::SendMessage(gameh,WM_LBUTTONUP,0,lparam);  // 
							  //��ȥ֮��ͳ���ͨ��  �������������ݸ���Ϊ0
							  chessdata[ptend.x][ptend.y] = chessdata[ptstart.x][ptstart.y] = 0;
						 }
					}
			  }			  
		  }
	 }
}