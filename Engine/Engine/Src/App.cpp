#include "Application.h"

#include "SoftRender.h"
#include "GuiControls.h"
#include "Config.h"

int main() 
{
    SoftRender::Init();

    Aplication app;
    app.Set_RenderGUI_Function(GUI_Controls::DrawGUI);
    app.Set_Render_Function(SoftRender::Render);
    app.Run();
    return 0;
}
