#include "SpriteRenderer.h"
#include "../ResourceManager.h"

namespace ENGINE
{
    //SpriteRenderer::SpriteRenderer(LPCSTR name, UINT divX, UINT divY) : divide({ 1.0f / divX, 1.0f / divY })
    SpriteRenderer::SpriteRenderer(std::vector<ENGINE::TotalResource> vResources)// : divide({ 1.0f / vResources.divX, 1.0f / resource.divY })
    {
        ChangeSpritese(vResources[0]);
    }

    VOID SpriteRenderer::SetSrc(UINT cx, UINT cy)
    {
        //뭉쳐있는 이미지를 잘라서 해당 이미지만 설정한다.
        sprites->SliceSource(cx * localSize.cx, cy * localSize.cy, localSize.cx, localSize.cy);
    }

    VOID SpriteRenderer::Operate(GameObject* Owner) 
    {
        if (sprites) 
            pos = Owner->GetTransform()->position;
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
        if (sprites) 
            sprites->TransparentBlt(pos.x, pos.y);
    }

    VOID SpriteRenderer::ChangeSpritese(ENGINE::TotalResource vResource)
    {
        sprites = ResourceMgr->GetBitmap(vResource.name);

        localSize = sprites->GetBitmapSize();
        localSize.cx *= vResource.divide.x;
        localSize.cy *= vResource.divide.y;
        size = localSize;
        SetSrc(0, 0);
    }
}