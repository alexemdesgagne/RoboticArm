#pragma once

#include <Qt3DExtras/Qt3DWindow>

class Q3DView : public Qt3DExtras::Qt3DWindow
{
	Q_OBJECT

public:
	Q3DView();
	~Q3DView();
};
