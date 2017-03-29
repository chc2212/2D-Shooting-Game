#ifndef TEST_C_APPLICATION_H
#define TEST_C_APPLICATION_H


class C_Application
{
public:

	
	typedef unsigned int T_PressedKey;

	C_Application(int screenWidth, int screenHeight);
	~C_Application();

	/// Tick is called on fix framerate (50fps)
	void Tick(T_PressedKey pressedKeys);
	
	
	bool Collision_Detection(struct Rect Rect1, struct Rect Rect2);
	bool Collision_Detection2(struct Rect Rect1, struct Rect Rect2);
	bool Collision_Detection3(struct Rect Rect1, struct Rect Rect2);
	void InitialClockObjects(int number, int m_ScreenWidth, int m_ScreenHeight);
	void ClockObject(int CenterX, int CenterY, int radius);


	static const T_PressedKey s_KeyLeft  = 0x01;
	static const T_PressedKey s_KeyUp    = 0x02;
	static const T_PressedKey s_KeyRight = 0x04;
	static const T_PressedKey s_KeyDown  = 0x08;
	static const T_PressedKey s_KeySpace = 0x10;

private:

	const int	m_ScreenWidth;
	const int	m_ScreenHeight;	
	
	// Members for sample tick
	int			m_CannonX;
	int			m_CannonY;

};

#endif // #ifndef TEST_C_APPLICATION_H
