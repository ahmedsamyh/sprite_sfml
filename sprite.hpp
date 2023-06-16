#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SFML/Graphics.hpp>

#ifndef TEX_PATH
#define TEX_PATH "res/gfx/"
#endif

namespace momo {
struct Sprite : public sf::Drawable {
  sf::Texture &sf_tex;
  sf::Sprite sf_spr;
  int hframe, vframe;
  size_t hframes, vframes;
  sf::Vector2u size;
  float time_per_frame;
  float accumulated;

  Sprite(sf::Texture &tex);
  Sprite(sf::Texture &tex, size_t _hframes, size_t _vframes = 1);

  void change_vframe(int f);
  void change_hframe(int f);

  /**
   * Animate hframes
   * \param delta delta time.
   **/
  void animate(float delta);

  // sf::Sprite wrappers
  const sf::Texture *getTexture() const;
  const sf::IntRect &getTextureRect() const;
  const sf::Color &getColor() const;
  sf::FloatRect getLocalBounds() const;
  sf::FloatRect getGlobalBounds() const;
  void setPosition(float x, float y);
  void setPosition(const sf::Vector2f &position);
  void setRotation(float angle);
  void setScale(float factorX, float factorY);
  void setScale(const sf::Vector2f &factors);
  void setOrigin(float x, float y);
  void setOrigin(const sf::Vector2f &origin);
  const sf::Vector2f &getPosition() const;
  float getRotation() const;
  const sf::Vector2f &getScale() const;
  const sf::Vector2f &getOrigin() const;
  void move(float offsetX, float offsetY);
  void move(const sf::Vector2f &offset);
  void rotate(float angle);
  void scale(float factorX, float factorY);
  void scale(const sf::Vector2f &factor);

  size_t width() const;
  size_t height() const;
  void center_origin();

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
} // namespace momo

#endif /* _SPRITE_H_ */
//////////////////////////////////////////////////
#ifdef SPRITE_IMPLEMENTATION

namespace momo {
Sprite::Sprite(sf::Texture &tex)
    : sf_tex(tex), hframe(0), vframe(0), hframes(1), vframes(1),
      time_per_frame(0.25f), accumulated(0.f) {
  sf_spr.setTexture(sf_tex);
  size = sf_tex.getSize();
}

Sprite::Sprite(sf::Texture &tex, size_t _hframes, size_t _vframes)
    : sf_tex(tex), hframe(0), vframe(0), hframes(_hframes), vframes(_vframes),
      time_per_frame(0.25f), accumulated(0.f) {

  sf_spr.setTexture(sf_tex);
  size = sf_tex.getSize();

  size.x = unsigned int(size.x / hframes);
  size.y = unsigned int(size.y / vframes);

  change_vframe(0);
  change_hframe(0);
}

void Sprite::change_vframe(int f) {
  vframe = f;

  if (vframe < 0) {
    vframe = int(vframes - 1);
  }
  if (vframe > vframes - 1) {
    vframe = 0;
  }

  sf_spr.setTextureRect(
      sf::IntRect(int(hframe * size.x), int(vframe * size.y), size.x, size.y));
}

void Sprite::change_hframe(int f) {
  hframe = f;

  if (hframe < 0) {
    hframe = int(hframes - 1);
  }
  if (hframe > hframes - 1) {
    hframe = 0;
  }

  sf_spr.setTextureRect(
      sf::IntRect(int(hframe * size.x), int(vframe * size.y), size.x, size.y));
}
// sf::Sprite wrappers
const sf::Texture *Sprite::getTexture() const { return sf_spr.getTexture(); }
const sf::IntRect &Sprite::getTextureRect() const {
  return sf_spr.getTextureRect();
}
const sf::Color &Sprite::getColor() const { return sf_spr.getColor(); }
sf::FloatRect Sprite::getLocalBounds() const { return sf_spr.getLocalBounds(); }
sf::FloatRect Sprite::getGlobalBounds() const {
  return sf_spr.getGlobalBounds();
}
void Sprite::setPosition(float x, float y) { sf_spr.setPosition(x, y); }
void Sprite::setPosition(const sf::Vector2f &position) {
  sf_spr.setPosition(position);
}
void Sprite::setRotation(float angle) { sf_spr.setRotation(angle); }
void Sprite::setScale(float factorX, float factorY) {
  sf_spr.setScale(factorX, factorY);
}
void Sprite::setScale(const sf::Vector2f &factors) { sf_spr.setScale(factors); }
void Sprite::setOrigin(float x, float y) { sf_spr.setOrigin(x, y); }
void Sprite::setOrigin(const sf::Vector2f &origin) { sf_spr.setOrigin(origin); }
const sf::Vector2f &Sprite::getPosition() const { return sf_spr.getPosition(); }
float Sprite::getRotation() const { return sf_spr.getRotation(); }
const sf::Vector2f &Sprite::getScale() const { return sf_spr.getScale(); }
const sf::Vector2f &Sprite::getOrigin() const { return sf_spr.getOrigin(); }
void Sprite::move(float offsetX, float offsetY) {
  sf_spr.move(offsetX, offsetY);
}
void Sprite::move(const sf::Vector2f &offset) { sf_spr.move(offset); }
void Sprite::rotate(float angle) { sf_spr.rotate(angle); }
void Sprite::scale(float factorX, float factorY) {
  sf_spr.scale(factorX, factorY);
}
void Sprite::scale(const sf::Vector2f &factor) { sf_spr.scale(factor); }

size_t Sprite::width() const { return size.x; }

size_t Sprite::height() const { return size.y; }

void Sprite::center_origin() { setOrigin(width() / 2.f, height() / 2.f); }

void Sprite::animate(float delta) {
  accumulated += delta;
  if (accumulated >= time_per_frame) {
    accumulated -= time_per_frame;

    change_hframe(hframe + 1);
  }
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {

  target.draw(sf_spr, states);
}

} // namespace momo
#endif
