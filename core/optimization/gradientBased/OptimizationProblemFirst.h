/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - liboptimization - An optimization/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
#ifndef _OPTIMIZATIONPROBLEMFIRST_OPTIMIZATION_H
#define _OPTIMIZATIONPROBLEMFIRST_OPTIMIZATION_H

#include <iostream>

#include <core/basics/NonCopyable.h>
#include <core/vector/VectorT.h>

namespace NICE {

/**
 * \defgroup optimization_problems Optimization Problems (Objective Functions)
 *
 * This module contains the base classes for user defined
 * nonlinear minimization problems:
 * objective functions together with their derivatives.
 * You will probably have to implement a subclass of one of these base classes.
 */

/**
 * Base class for nonlinear minimization problems providing
 * 1st order derivatives.
 * Also read the documentation of \c OptimizationProblemSecond.
 *
 * \ingroup optimization_problems
 */
class OptimizationProblemFirst : private NonCopyable {
public:
  //! Default constructor
  inline OptimizationProblemFirst(unsigned int dimension)
      : m_gradientCache(dimension, 0), m_positionCache(dimension,0) {
    init();
  }

  virtual ~OptimizationProblemFirst();

  /**
   * Initialize the optimization problem (reset caches etc.)
   */
  inline void init() {
    m_objectiveCached = false;
    m_positionCached = false;
    m_gradientCached = false;
    m_gradientNormCached = false;
  }

  /**
   * The dimension of the optimization problem
   * (the dimension of the parameter space).
   */
  inline unsigned int dimension() const {
    return m_gradientCache.size();
  }

  /**
   * Get the value of the objective function at the current position.
   * The objective function will be evaluated only if the position has changed
   * via \c applyStep().
   */
  inline double objective() {
    if (!m_objectiveCached) {
      m_objectiveCache = computeObjective();
      m_objectiveCached = true;
    }
    return m_objectiveCache;
  }

  /**
   * Get the current position.
   */
  inline const Vector& position() {
    if (!m_positionCached) {
      m_positionCache.resize(dimension());
      computePosition(m_positionCache);
      m_positionCached = true;
    }
    return m_positionCache;
  }

  /**
   * Compute the gradient of the objective function at the current position.
   * @note If you are using \c OptimizationProblemSecond, don't call
   *       \c computeGradient(), unless you don't need the Hessian.
   */
  inline void computeGradient() {
    m_gradientNormCached = false;
    computeGradient(m_gradientCache);
    m_gradientCached = true;
  }

  /**
   * Get the gradient of the objective function as computed by the last call
   * to \c computeGradient().
   */
  inline const Vector& gradientCached() {
    return m_gradientCache;
  }

  /**
   * Get the gradient of the objective function at the current position
   * in parameter space.
   * The gradient will be computed if the gradient cache is out of date.
   */
  inline const Vector& gradientCurrent() {
    if (!m_gradientCached) {
      computeGradient();
    }
    return m_gradientCache;
  }

  /**
   * Get the Euclidean norm of the gradient of the objective function
   * as computed by the last call to \c computeGradient().
   */
  inline double gradientNormCached() {
    if (!m_gradientNormCached) {
      m_gradientNormCache = gradientCached().normL2();
      m_gradientNormCached = true;
    }
    return m_gradientNormCache;
  }

  /**
   * Get the Euclidean norm of the gradient of the objective function.
   * The gradient will be computed if the gradient cache is out of date.
   */
  inline double gradientNormCurrent() {
    if (!m_gradientNormCached || !m_gradientCached) {
      m_gradientNormCache = gradientCurrent().normL2();
      m_gradientNormCached = true;
    }
    return m_gradientNormCache;
  }

  /**
   * Apply a step to the current position in parameter space.
   * @param step The change to be applied to the current position
   */
  inline void applyStep(const Vector& step) {
    invalidateCaches();
    doApplyStep(step);
  }

  /**
   * Unapply a step to the current position in parameter space.
   * Is equivalent to \c apply(-step); .
   * @param step The change to be unapplied to the current position
   */
  inline void unapplyStep(const Vector& step) {
    invalidateCaches();
    doUnapplyStep(step);
  }

  /**
   * Invalidate all caches. Call this method after changing the position
   * in parameter space outside of doApplyStep() and doUnapplyStep().
   */
  virtual void invalidateCaches() {
    m_objectiveCached = false;
    m_positionCached = false;
    m_gradientCached = false;
  }

protected:
  /**
   * The current position in parameter space to be used by subclasses
   * which do NOT have their own representation for this data.
   * Using \c parameters() is recommended.
   */
  inline Vector& parameters() {
    m_positionCache.resize(dimension());
    return m_positionCache;
  }

  /**
   * The current position in parameter space to be used by subclasses
   * which do NOT have their own representation for this data.
   * Using \c parameters() / \c parametersConst() is recommended.
   */
  inline const Vector& parametersConst() const {
    if (m_positionCache.size() != dimension()) {
      fthrow(Exception,
             "parametersConst(): data not initialized. Call nonconst version of parameters() first");
    }
    return m_positionCache;
  }

  /**
   * Compute the value of the objective function at the current position.
   * @return value of the objective function
   */
  virtual double computeObjective() = 0;

  /**
   * Compute the gradient of the objective function at the current position.
   * @param newGradient Output parameter for the gradient of the objective
   *        function. Be careful: \c newGradient is the <b>same</b> object
   *        as \c gradient(). If you need to access (the old) \c gradient()
   *        during the computation, first make a copy.
   */
  virtual void computeGradient(Vector& newGradient) = 0;

  /**
   * Compute the current position in parameter space.
   * Only needs to be implemented in subclasses if \c parameters() is not used
   * in the subclass to store the position in parameter space.
   * @param pos Output parameter for the position in parameter space.
   *        Be careful: \c pos is the <b>same</b> object
   *        as \c position(). If you need to access \c position()
   *        during the computation, first make a copy.
   */
  virtual void computePosition(Vector& pos);

  /**
   * Apply a step to the current position in parameter space.
   * Only needs to be implemented in subclasses if \c parameters() is not used
   * in the subclass to store the position in parameter space.
   * @note If you want to renormalize the position vector after applying
   * the step, this method is the right place. If you use \c parameters()
   * to store the position, you should first call
   * \c OptimizationProblemFirst::doApplyStep(step);
   * and renormalize after that.
   * In this situation, you do not have to worry about \c doUnapplyStep().
   * The default implementation is just fine, as the position will be reset
   * to a backup copy of the previous position. So there are no normalization
   * issues involved in \c doUnapplyStep().
   * @param step The change to be applied to the current position
   */
  virtual void doApplyStep(const Vector& step);

  /**
   * Unapply a step to the current position in parameter space.
   * Only needs to be implemented in subclasses if \c parameters() is not used
   * in the subclass to store the position in parameter space.
   * @param step The change to be applied to the current position
   */
  virtual void doUnapplyStep(const Vector& step);

private:
  bool m_positionCached;
  bool m_objectiveCached;
  bool m_gradientCached;
  bool m_gradientNormCached;

  double m_objectiveCache;
  Vector m_positionCache;
  Vector m_previousPosition;
  Vector m_gradientCache;
  double m_gradientNormCache;

  friend class OptimizationProblemSecond;
};

}; // namespace NICE

#endif /* _OPTIMIZATIONPROBLEMFIRST_OPTIMIZATION_H */
