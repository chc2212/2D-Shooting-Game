#include "C_Application.h"
#include "graphics.h"
#include "time.h"
#include <cmath>
#include <vector>
#include <ctime>


# define M_PI 3.14159265358979323846
# define initial_clock_num 2

const float projectile_speed = 0.65;
float m_CannonX2 = 0;
float m_CannonY2 = 30;
float m_CannonX3 = 10;
float m_CannonY3 = 0;
float m_CannonX4 = -10;
float m_CannonY4 = 0;
float angle=1;

int projectil_num=0;

struct Line{
	float x1,y1,x2,y2;
};

struct Rect{
	float leftTopX,leftTopY,rightBottomX,rightBottomY;
};

std::vector <Line> projectile;
std::vector <Rect> clocks;
std::vector <int> clocks_speed_directionX;
std::vector <int> clocks_speed_directionY;



C_Application::C_Application(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth)
	, m_ScreenHeight(screenHeight)
	, m_CannonX(m_ScreenWidth/2)   //m_CannonX is not a x point of top of triangle. This will be used for x of bottom base of the triangle. 
	, m_CannonY(m_ScreenHeight/1.1) //m_CannonY is not a y point of top of triangle. This will be used for y of bottom base of the triangle.
{

}

C_Application::~C_Application()
{
	projectile.clear();
	clocks.clear();
	clocks_speed_directionX.clear();
	clocks_speed_directionY.clear();
}

void C_Application::Tick(T_PressedKey pressedKeys)
{
	// Sample tick

	// Clear screen on cannon position
	FillRect(0, 0, m_ScreenWidth, m_ScreenHeight, GetRGB(0, 0, 0)); 


	// -----------------------------Key processing--------------------------
	if(pressedKeys & s_KeyLeft)
	{
		if(m_CannonY2 > 0 || m_CannonX2 < 0 ) // Cannon degree should be under |90|
		{
			angle = -1;
			float tempX = m_CannonX2;
			float tempY = m_CannonY2;

			m_CannonX2 = tempX*cos(angle*M_PI/180) - tempY*sin(angle*M_PI/180);
			m_CannonY2 = tempY*cos(angle*M_PI/180) + tempX*sin(angle*M_PI/180);

			tempX = m_CannonX3;
			tempY = m_CannonY3;

			m_CannonX3 = tempX*cos(angle*M_PI/180) - tempY*sin(angle*M_PI/180);
			m_CannonY3 = tempY*cos(angle*M_PI/180) + tempX*sin(angle*M_PI/180);

			tempX = m_CannonX4;
			tempY = m_CannonY4;

			m_CannonX4 = tempX*cos(angle*M_PI/180) - tempY*sin(angle*M_PI/180);
			m_CannonY4 = tempY*cos(angle*M_PI/180) + tempX*sin(angle*M_PI/180);
		}
	}

	if(pressedKeys & s_KeyRight)
	{
		if(m_CannonY2 > 0 || m_CannonX2 > 0 ) // Cannon degree should be under |90|
		{
			angle = 1;
			float tempX = m_CannonX2;
			float tempY = m_CannonY2;

			m_CannonX2 = tempX*cos(angle*M_PI/180) - tempY*sin(angle*M_PI/180);
			m_CannonY2 = tempY*cos(angle*M_PI/180) + tempX*sin(angle*M_PI/180);	

			tempX = m_CannonX3;
			tempY = m_CannonY3;

			m_CannonX3 = tempX*cos(angle*M_PI/180) - tempY*sin(angle*M_PI/180);
			m_CannonY3 = tempY*cos(angle*M_PI/180) + tempX*sin(angle*M_PI/180);

			tempX = m_CannonX4;
			tempY = m_CannonY4;

			m_CannonX4 = tempX*cos(angle*M_PI/180) - tempY*sin(angle*M_PI/180);
			m_CannonY4 = tempY*cos(angle*M_PI/180) + tempX*sin(angle*M_PI/180);
		}
	}


	//m_Cannon 2, 3 ,4 are vectors
	if(pressedKeys & s_KeySpace)
	{
		//Object creation
		struct Line projectile_rect = {m_CannonX - 1.3*m_CannonX2,  m_CannonY -  1.3*m_CannonY2, m_CannonX - 1.5*m_CannonX2, m_CannonY -  1.5*m_CannonY2};
		projectile.push_back(projectile_rect);		
	}


	//--------------------------------Collision Detection----------------------------------------//
	//1. Clock and Border of Screen
	for(int i=0;i<clocks.size();i++)
	{
		//left border
		if(clocks[i].leftTopX <= 0)
		{
			clocks_speed_directionX[i] *= -1;
			clocks_speed_directionY[i] *= 1;
		}
		//top border
		if(clocks[i].leftTopY <= 0)
		{
			clocks_speed_directionX[i] *= 1;
			clocks_speed_directionY[i] *= -1;
		}
		//right border
		if(clocks[i].rightBottomX >= m_ScreenWidth)
		{
			clocks_speed_directionX[i] *= -1;
			clocks_speed_directionY[i] *= 1;
		}
		//bottom border
		if(clocks[i].rightBottomY >= m_ScreenHeight)
		{
			clocks_speed_directionX[i] *= 1;
			clocks_speed_directionY[i] *= -1;
		}	
	}

	//2. Clock and Projectile
	for(int i=0;i<projectile.size();i++)
		for(int j=0;j<clocks.size();j++)
		{
			//make virtual rect from line
			struct Rect temp_rect = {projectile[i].x1,projectile[i].y1,projectile[i].x1,projectile[i].y1};
			//collision detection
			if(Collision_Detection(temp_rect,clocks[j]))
			{
				//create new two clocks						
				if((clocks[j].rightBottomX - clocks[j].leftTopX) >= 12) //if the clock is too small, don't make new clocks 
				{
					ClockObject(clocks[j].leftTopX + (clocks[j].rightBottomX - clocks[j].leftTopX)/2 - (clocks[j].rightBottomX - clocks[j].leftTopX)/2, clocks[j].leftTopY + (clocks[j].rightBottomY - clocks[j].leftTopY)/2,(clocks[j].rightBottomX - clocks[j].leftTopX)/4); 
					ClockObject(clocks[j].leftTopX + (clocks[j].rightBottomX - clocks[j].leftTopX)/2 + (clocks[j].rightBottomX - clocks[j].leftTopX)/2, clocks[j].leftTopY + (clocks[j].rightBottomY - clocks[j].leftTopY)/2,(clocks[j].rightBottomX - clocks[j].leftTopX)/4); 				
				}

				//delete previous clock
				clocks.erase(clocks.begin()+j);			
				clocks_speed_directionX.erase(clocks_speed_directionX.begin()+j);
				clocks_speed_directionY.erase(clocks_speed_directionY.begin()+j);		

			}		
		}


		//3. Clock and Clock
		for(int i=0;i<clocks.size();i++)
		{
			for(int j=0; j<clocks.size();j++)
			{
				if(i !=j && Collision_Detection2(clocks[i],clocks[j]))
				{	
					clocks_speed_directionX[i] *= -1;
					clocks_speed_directionY[i] *= -1;
				}
			}	
		}

		//--------------------------------Movement----------------------------------------

		//1. Projectile
		for (int i=0;i<projectile.size();i++)
		{
			projectile[i].x1 += - projectile_speed * m_CannonX2;
			projectile[i].y1 += - projectile_speed * m_CannonY2;
			projectile[i].x2 += - projectile_speed * m_CannonX2;
			projectile[i].y2 += - projectile_speed * m_CannonY2;
		}

		//Delete Projectile if it is out of screen
		for (int i=0;i<projectile.size();i++)
		{		
			if(projectile[i].x1 < -200) 
				projectile.erase(projectile.begin()+i);
			else if(projectile[i].x1 > m_ScreenWidth + 200) 
				projectile.erase(projectile.begin()+i);	
			else if(projectile[i].y1 < -200) 
				projectile.erase(projectile.begin()+i);	
			else if(projectile[i].y1 > m_ScreenHeight + 200) 
				projectile.erase(projectile.begin()+i);				
		}


		//2. Clock 

		for (int i=0;i<clocks.size();i++)
		{		
			clocks[i].leftTopX += 0.005 * clocks_speed_directionX[i];
			clocks[i].leftTopY += 0.005 *clocks_speed_directionY[i];
			clocks[i].rightBottomX += 0.005 *clocks_speed_directionX[i];
			clocks[i].rightBottomY += 0.005 * clocks_speed_directionY[i];

		}

		for (int i=0;i<clocks.size();i++)
		{
			for(int j=0;j<clocks.size();j++)
				if(i != j && Collision_Detection3(clocks[i],clocks[j]))//prevent clock from stuck
				{
					clocks[i].leftTopX += 0.005 * clocks_speed_directionX[i] * 4;
					clocks[i].leftTopY += 0.005 *clocks_speed_directionY[i] * 4;
					clocks[i].rightBottomX += 0.005 *clocks_speed_directionX[i] * 4;
					clocks[i].rightBottomY += 0.005 * clocks_speed_directionY[i] * 4;						
				}

				//if clock is out of screen, adjust the direction and the speed
				if(clocks[i].leftTopX<=-30 && 0.005 * clocks_speed_directionX[i] <0.1)
					clocks_speed_directionX[i] = abs(4*clocks_speed_directionX[i]); 
				if(clocks[i].leftTopY<=-30 && 0.005 * clocks_speed_directionY[i] <0.1)
					clocks_speed_directionY[i] = abs(4*clocks_speed_directionY[i]); 
				if(clocks[i].rightBottomX >= m_ScreenWidth + 30 && 0.005 * clocks_speed_directionX[i] > -0.1)
					clocks_speed_directionX[i] = -1 * abs(4*clocks_speed_directionX[i]);
				if(clocks[i].rightBottomY >= m_ScreenHeight +30 && 0.005 * clocks_speed_directionY[i] > -0.1)
					clocks_speed_directionY[i] = -1 * abs(4*clocks_speed_directionY[i]);


				//if clock is out of screen, delete that clock.
				if(clocks[i].leftTopX<=-10 || clocks[i].leftTopY<=-10 || clocks[i].rightBottomX >= m_ScreenWidth + 10  || clocks[i].rightBottomY >= m_ScreenHeight +10 )
				{
					clocks.erase(clocks.begin()+i);			
					clocks_speed_directionX.erase(clocks_speed_directionX.begin()+i);
					clocks_speed_directionY.erase(clocks_speed_directionY.begin()+i);		
				}		

		}




		//--------------------------------- Drawing---------------------------------------

		//1. Cannon
		DrawLine(m_CannonX - m_CannonX2, m_CannonY -  m_CannonY2, m_CannonX - m_CannonX3, m_CannonY -  m_CannonY3, GetRGB(0,   255,   0));
		DrawLine(m_CannonX - m_CannonX2, m_CannonY -  m_CannonY2, m_CannonX - m_CannonX4, m_CannonY -  m_CannonY4, GetRGB(0,   255,   0));
		DrawLine(m_CannonX - m_CannonX3, m_CannonY -  m_CannonY3, m_CannonX - m_CannonX4, m_CannonY -  m_CannonY4, GetRGB(0,  255,   0));

		//2. Projectile 
		for (int i=0;i<projectile.size();i++)
			DrawLine(projectile[i].x1, projectile[i].y1, projectile[i].x2,  projectile[i].y2, GetRGB(255,   255,   255));


		//3. Clock
		int clock_centerX=0;
		int clock_centerY=0;	

		//Initiial two clocks creation
		if(clocks.size() == 0)
			InitialClockObjects(initial_clock_num,m_ScreenWidth,m_ScreenHeight);


		//Drawing clocks
		for (int i=0;i<clocks.size();i++)
		{
			//Draw rectangle
			DrawLine(clocks[i].leftTopX, clocks[i].leftTopY, clocks[i].rightBottomX,clocks[i].leftTopY, GetRGB(255,   0,   0)); //Top-side
			DrawLine(clocks[i].rightBottomX,  clocks[i].leftTopY, clocks[i].rightBottomX, clocks[i].rightBottomY, GetRGB(255,   0,   0)); //Right-side
			DrawLine(clocks[i].rightBottomX, clocks[i].rightBottomY, clocks[i].leftTopX, clocks[i].rightBottomY, GetRGB(255,   0,   0)); //Bottom-side
			DrawLine(clocks[i].leftTopX, clocks[i].rightBottomY, clocks[i].leftTopX, clocks[i].leftTopY, GetRGB(255,   0,   0)); //Left-side		

			//Draw clock hands
			time_t currentTime;
			struct tm *localTime;

			time( &currentTime );                  
			localTime = localtime( &currentTime );  

			int hour   = localTime->tm_hour;
			int min    = localTime->tm_min;
			int sec    = localTime->tm_sec;

			//get cetner point and radius of Rectangle  
			int radiusX = (clocks[i].rightBottomX - clocks[i].leftTopX)/2;
			int radiusY = (clocks[i].rightBottomY - clocks[i].leftTopY)/2;
			int temp_CenterX = clocks[i].leftTopX + radiusX;	
			int temp_CenterY = clocks[i].leftTopY + radiusY;

			//get radian and x,y for each clock hands
			float RadianSec = (((6 * sec)-90) * (M_PI / 180));

			int sec_x = int((radiusX * cos(RadianSec)));
			int sec_y = int((radiusY * sin(RadianSec)));

			float RadianMin = (((6 * min)-90) * (M_PI / 180));

			int min_x = int((radiusX * cos(RadianMin)));
			int min_y = int((radiusY * sin(RadianMin)));

			float RadianHour = (((30 * hour)-90)* (M_PI / 180));

			int hour_x = int((radiusX * cos(RadianHour)));
			int hour_y = int((radiusY * sin(RadianHour)));	

			DrawLine(temp_CenterX,    temp_CenterY,    temp_CenterX+sec_x, temp_CenterY+sec_y, GetRGB(0,   255,   255));
			DrawLine(temp_CenterX,    temp_CenterY,    temp_CenterX+min_x, temp_CenterY+min_y, GetRGB(255,   255,   0));
			DrawLine(temp_CenterX,    temp_CenterY,    temp_CenterX+hour_x, temp_CenterY+hour_y, GetRGB(0,   0,   255));
		}



}

bool C_Application::Collision_Detection(struct Rect Rect1, struct Rect Rect2)
{
	if(Rect1.rightBottomY < Rect2.leftTopY-2 || Rect1.leftTopY-2 > Rect2.rightBottomY || Rect1.rightBottomX < Rect2.leftTopX-2 || Rect1.leftTopX-2 > Rect2.rightBottomX)
		return false;
	else return true;
}

bool C_Application::Collision_Detection2(struct Rect Rect1, struct Rect Rect2) //different parameter of border 
{
	if(Rect1.rightBottomY < Rect2.leftTopY || Rect1.leftTopY > Rect2.rightBottomY || Rect1.rightBottomX < Rect2.leftTopX || Rect1.leftTopX > Rect2.rightBottomX)
		return false;
	else return true;
}


bool C_Application::Collision_Detection3(struct Rect Rect1, struct Rect Rect2) //different parameter of border 
{
	if(Rect1.rightBottomY < Rect2.leftTopY + 1 || Rect1.leftTopY +1 > Rect2.rightBottomY || Rect1.rightBottomX < Rect2.leftTopX  +1  || Rect1.leftTopX +1 > Rect2.rightBottomX)
		return false;
	else return true;
}

//Creating Initial Clock Objects
void C_Application::InitialClockObjects(int number, int m_ScreenWidth, int m_ScreenHeight)
{
	for(int i=0;i<number;i++)
	{			
		srand (time(NULL));			
		int randomCenterX = rand() % (m_ScreenWidth - 200) + 100; 
		int randomCenterY = rand() % (m_ScreenHeight - 200) + 100;


		bool overlap = true;
		//Check if initial clocks are overlapped.
		while(overlap == true)
		{
			overlap = false;
			for (int j=0;j<clocks.size();j++)
			{
				// if they are overlapped, get new randomX, Y.
				if(abs(clocks[j].leftTopX + 50 - randomCenterX) <= 100 &&  abs(clocks[j].leftTopY + 50 - randomCenterY) <= 100) 
				{						
					randomCenterX = rand() % (m_ScreenWidth - 200) + 100; 
					randomCenterY = rand() % (m_ScreenHeight - 200) + 100;	
					overlap=true;
				}	
			}
		}

		//Create clock objects
		struct Rect clock_rect = {randomCenterX-50,randomCenterY-50,randomCenterX+50,randomCenterY+50};
		clocks.push_back(clock_rect);


		//initial random speed and direction
		srand (randomCenterX);			

		//Managing direction and speed using one random vector
		int randomSpeedDirectionX = rand() % (m_ScreenWidth);	
		int randomSpeedDirectionY = rand() % (m_ScreenHeight);

		int directionVectorX = clocks[i].leftTopX + 50 - randomSpeedDirectionX;
		int directionVectorY = clocks[i].leftTopY + 50 - randomSpeedDirectionY;

		//create clock speed and direction objects
		clocks_speed_directionX.push_back(directionVectorX);
		clocks_speed_directionY.push_back(directionVectorY);


	}

}

//Creating Clock Object
void C_Application::ClockObject(int CenterX, int CenterY, int radius)
{
	//Create clock objects
	struct Rect clock_rect = {CenterX-radius,CenterY-radius,CenterX+radius,CenterY+radius};
	clocks.push_back(clock_rect);		

	//initial random speed and direction
	srand (CenterX);					


	int randomSpeedDirectionX = rand() % 2000 + (-1000);		
	int randomSpeedDirectionY = rand() % 2000 + (-1000);		


	int directionVectorX = CenterX - randomSpeedDirectionX;
	int directionVectorY = CenterY - randomSpeedDirectionY;

	//create clock speed and direction objects 
	clocks_speed_directionX.push_back(directionVectorX);
	clocks_speed_directionY.push_back(directionVectorY);
}