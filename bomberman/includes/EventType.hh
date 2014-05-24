#ifndef __EVENTTYPE_H__
# define __EVENTTYPE_H__

namespace Event{

  namespace Info{
    /* #### Event Type ##### */
    enum Type{
      Network = -1,
      selfMovement, speedModifier, freezeMovement, /*phisix::vector*/
      setFriction,/* phisix */
      PlaceDot, Immunity, lifeLoss, lifeGain, revive, /* Health */
      RequireMovement, Colliding,/* collider::movable */
      FireExplosion, ElectricityExplosion, IceExplosion, LifeExplosion, /* status*/
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
