#ifndef __EVENTTYPE_H__
# define __EVENTTYPE_H__

namespace Event{

  namespace Info{
    /* #### Event Type ##### */
    enum Type{
      Network = -1,
      EntityEnable, EntityDisable, EntityFlush, EntitySerialize, beginGame,
      selfMovement, speedModifier, freezeMovement, /*phisix::vector*/
      setFriction,/* phisix */
      PlaceDot, Immunity, lifeLoss, lifeGain, revive, dead, /* Health */
      RequireMovement, Colliding,/* collider::movable */
      disableCollision,/*collider::static*/
      FireExplosion, ElectricityExplosion, IceExplosion, LifeExplosion, GlyphExplosion, /* status*/
      plantBomb, selfPlantBomb, addElement, /* plant Bomb */
      Keyboard, ChangeKeyConfig, /* keyBoard */
      isMute, /* quite a lot */
      LootBonus, BonusLocation, TakeBonus, /* Bonus */
      Explosion, /* explode and bloc */
      SocketGlyph, EnableGlyph, extinctGlyph, /* Runes */
      BombReloaded, BombReleased, IncreaseBombStack,/* UI */
      isOnFire, isOnLife, isOnIce, isOnElectricity, /* display */ 
      Clock, Refresh,
    };
  };

  namespace Info{
    /* ###### Event Priority ##### */
    enum Priority{
      low, medium, high
    };
  };
};

#endif
