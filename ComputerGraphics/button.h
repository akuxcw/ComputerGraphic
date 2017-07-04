#include "graph.h"

class Button {
private:
	float m_fPosX, m_fPosY, m_fWidth, m_fHeight;
	char* name;
	void (*DownFunc)(), (*UpFunc)();
	bool m_bPressed;
	Color back, front;
	void selectFont(int size, int charset, const char* face) {
		HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
			charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
		HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
		DeleteObject(hOldFont);
	}
	void DrawString(const char* str) //��Ļ��ʾ����  
	{
		static int isFirstCall = 1;
		static GLuint lists;
		if (isFirstCall) {
			isFirstCall = 0;
			lists = glGenLists(128);// ����128����������ʾ�б���  
			wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		}
		// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�  
		for (; *str != '\0'; ++str) {
			glCallList(lists + *str);
		}
	}
public:
	Button() {
		this->m_bPressed = false;
	}
	Button(float x, float y, float w, float h, Color c1, Color c2, const char* name, void func()) {
		this->m_bPressed = false;
		this->m_fPosX = x;
		this->m_fPosY = y;
		this->m_fWidth = w;
		this->m_fHeight = h;
		this->back = c1;
		this->front = c2;
		this->name = (char*)malloc(strlen(name) + 1);
		strcpy_s(this->name, strlen(name) + 1, name);
		this->DownFunc = func;
	}
	void Display() {
		glColor3f(back.x, back.y, back.z);
		if (m_bPressed) {
			glRectf(m_fPosX, m_fPosY + 0.9*m_fHeight, m_fPosX + 0.9*m_fWidth, m_fPosY);
			glColor3f(front.x, front.y, front.z);
			selectFont(0.9 * (m_fHeight + 2), ANSI_CHARSET, "Comic Sans MS");  //���������ϵͳ�ļ���Ѱ��  
			glRasterPos2i(m_fPosX, m_fPosY + m_fHeight / 4);  //��ʼλ��  
			DrawString(name);   //������ַ���
		}
		else {
			glRectf(m_fPosX, m_fPosY + m_fHeight, m_fPosX + m_fWidth, m_fPosY);
			glColor3f(front.x, front.y, front.z);
			selectFont(m_fHeight + 5, ANSI_CHARSET, "Comic Sans MS");  //���������ϵͳ�ļ���Ѱ��  
			glRasterPos2i(m_fPosX, m_fPosY + m_fHeight / 4);  //��ʼλ��  
			DrawString(name);   //������ַ���
		}
	}
	bool OnMouseDown(int mousex, int mousey) {
		if (mousex >= m_fPosX && mousex <= m_fPosX + m_fWidth &&
			mousey >= m_fPosY && mousey <= m_fPosY + m_fHeight) {
			m_bPressed = true;
			DownFunc();
			Display();
			return true;
		}
		return false;
	}
	void OnMouseUp() {
//		UpFunc();
		m_bPressed = false;
	}
};

extern vector<Button *> button_table;

void init_button();