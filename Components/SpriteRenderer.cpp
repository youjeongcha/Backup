#include "SpriteRenderer.h"
#include "../ResourceManager.h"

namespace ENGINE
{
    SpriteRenderer::SpriteRenderer(LPCSTR name, UINT divX, UINT divY) : divide({ 1.0f / divX, 1.0f / divY })
    {
        sprites = ResourceMgr->GetBitmap(name);

        localSize = sprites->GetBitmapSize();
        localSize.cx *= divide.x;
        localSize.cy *= divide.y;
        size = localSize;
        SetSrc(0, 0);
    }

    VOID SpriteRenderer::SetSrc(UINT cx, UINT cy)
    {
        sprites->SliceSource(cx * localSize.cx, cy * localSize.cy, localSize.cx, localSize.cy);
    }

    VOID SpriteRenderer::Operate(GameObject* Owner) 
    {
        if (sprites) pos = Owner->GetTransform()->position;
    }

    VOID SpriteRenderer::Reset()
    {
        if (sprites)
        {
            sprites->ResetSize();
            sprites->ResetPivot();
        }
    }

    VOID SpriteRenderer::SetScale(UINT cx, UINT cy)
    {
        size = { (LONG)(localSize.cx * cx), (LONG)(localSize.cy * cy) };
        sprites->SetDrawSize(size.cx, size.cy);
    }

    VOID SpriteRenderer::Draw()
    {
        if (sprites) sprites->TransparentBlt(pos.x, pos.y);
    }
}