#include "TransparentSprite.h"


TransparentSprite::TransparentSprite(const std::filesystem::path& spriteSheet, int numFrames)
    : m_NumFrames{ numFrames }
    , m_Sprite(new Tmpl8::Surface(spriteSheet.string().c_str()), m_NumFrames)
{}

void TransparentSprite::setPosition(float x, float y)
{
    setPosition({ x , y });
}

void TransparentSprite::setPosition(const Tmpl8::vec2& pos)
{
    m_Position = pos;
}

const Tmpl8::vec2& TransparentSprite::getPosition() const
{
    return m_Position;
}

int TransparentSprite::getWidth() const
{
    return m_Sprite.GetWidth();
}

int TransparentSprite::getHeight() const
{
    return m_Sprite.GetHeight();
}

void TransparentSprite::setFrame(int frame)
{
    while (frame < 0) frame += m_NumFrames;
    m_Frame = frame % m_NumFrames;
}

int TransparentSprite::getFrame() const
{
    return m_Frame;
}

void TransparentSprite::setAlpha(float alpha)
{
    m_Alpha = alpha;
}

float TransparentSprite::getAlpha() const
{
    return m_Alpha;
}

void TransparentSprite::render(Tmpl8::Surface& screen)
{
    int dstW = screen.GetWidth();
    int dstH = screen.GetHeight();
    int dstPitch = screen.GetPitch();
    int dstX = static_cast<int>(m_Position.x);
    int dstY = static_cast<int>(m_Position.y);

    int srcW = m_Sprite.GetWidth();
    int srcH = m_Sprite.GetHeight();
    int srcPitch = m_Sprite.GetSurface()->GetPitch();

    // Clipping
    int clipLeft = std::min(0, dstX);
    int clipTop = std::min(0, dstY);
    int clipRight = std::max(0, dstX + srcW - dstW);
    int clipBottom = std::max(0, dstY + srcH - dstH);

    int srcX = -clipLeft;
    int srcY = -clipTop;
    srcW -= clipRight - clipLeft;
    srcH -= clipBottom - clipTop;

    // If the sprite is completely off screen...
    if (dstX >= dstW || dstY >= dstH || srcW <= 0 || srcH <= 0) return;

    Tmpl8::Pixel* src = m_Sprite.GetBuffer() + (srcY * srcPitch) + (srcW * m_Frame) + srcX;
    Tmpl8::Pixel* dst = screen.GetBuffer() + (dstY * dstPitch) + dstX;

    for (int y = srcY; y < srcH; ++y)
    {
        for (int x = srcX; x < srcW; ++x)
        {
            Tmpl8::Pixel srcColor = *(src + y * srcPitch + x);
            Tmpl8::Pixel dstColor = *(dst + y * dstPitch + x);

            const float srcA = static_cast<float>(srcColor >> 24) / 255.0f * m_Alpha;
            const unsigned char srcR = static_cast<unsigned char>(srcColor >> 16);
            const unsigned char srcG = static_cast<unsigned char>(srcColor >> 8);
            const unsigned char srcB = static_cast<unsigned char>(srcColor);

            unsigned char dstR = static_cast<unsigned char>(dstColor >> 16);
            unsigned char dstG = static_cast<unsigned char>(dstColor >> 8);
            unsigned char dstB = static_cast<unsigned char>(dstColor);

            dstR = static_cast<unsigned char>(srcA * static_cast<float>(srcR) + (1.0f - srcA) * static_cast<float>(dstR));
            dstG = static_cast<unsigned char>(srcA * static_cast<float>(srcG) + (1.0f - srcA) * static_cast<float>(dstG));
            dstB = static_cast<unsigned char>(srcA * static_cast<float>(srcB) + (1.0f - srcA) * static_cast<float>(dstB));

            dstColor = static_cast<Tmpl8::Pixel>(dstR << 16) | static_cast<Tmpl8::Pixel>(dstG << 8) | static_cast<Tmpl8::Pixel>(dstB);

            *(dst + y * dstPitch + x) = dstColor;
        }
    }
}
