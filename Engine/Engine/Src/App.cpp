#include "Application.h"

#include "AssetRegistry.h"

#include "SoftRender.h"
#include "GuiControls.h"
#include "Config.h"

int main() 
{
    rendering::AssetRegistry::RegisterSprite({0, 0}, {RES_X, RES_Y}, { RES_X, RES_Y });

    Aplication app;
    app.Set_RenderGUI_Function(GUI_Controls::DrawGUI);
    app.Set_Render_Function(SoftRender::Render);
    app.Run();
    return 0;
}
