//
// C++ Interface: ArrayPlot
//
// Description: 
//
//
// Author: Marcel Brueckner <brueckner [at] informatik [dot] uni-jena [dot] de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef IMAGEDISPLAY_ARRAYPLOT_H
#define IMAGEDISPLAY_ARRAYPLOT_H

#include <QWidget>
#include <QMouseEvent>
#include <QGLWidget>
#include <core/basics/NonCopyable.h>
#include <core/basics/numerictools.h>

namespace NICE {

class ArrayPlot : public QGLWidget, private NICE::NonCopyable {
	Q_OBJECT;
public:
	ArrayPlot ( std::vector<double> probs,
						unsigned int width,
						unsigned int height,
            bool invertColors,
						QWidget* parent = NULL, 
						const char* name = NULL,
	               Qt::WFlags flags = 0 );
	
	virtual ~ArrayPlot(void);
	
	inline void setProb(unsigned int i, unsigned int j, double prob) {
		m_probs[i*m_width + j] = prob;
		
		if (prob > m_maxProb)
			m_maxProb = prob;
		
		if (prob < m_minProb)
			m_minProb = prob;
	}
	
	inline unsigned int img1(void) const {
		return m_xPos;
	}
	
	inline unsigned int img2(void) const {
		return m_yPos;
	}
	
	inline double prob (void) {
		return m_probs[m_xPos * m_height + m_yPos];
	}
  
  inline void reset (const std::vector<double>& newValues) {
    m_maxProb = -std::numeric_limits<double>::infinity();
    m_minProb = std::numeric_limits<double>::infinity();
    for (unsigned int i = 0; i < m_probs.size(); ++i) {
      m_probs[i] = newValues[i];
      m_maxProb = std::max(m_maxProb, m_probs[i]);
      m_minProb = std::min(m_minProb, m_probs[i]);
    }
  }
  
  inline void setMax (double max) {
    m_maxProb = max;
  }
  
  inline void setMin (double min) {
    m_minProb = min;
  }
	
	void loadFromFile (const char* path);
	
public slots:
	/**
   * Repaint this widget.
   */
  void repaint();

protected:
	virtual void paintGL(void);
	
	virtual void mousePressEvent(QMouseEvent* event);
		
private:
	void toColor ( double x, double & r, double & g, double & b );

	unsigned int m_width;
	unsigned int m_height;
	double m_maxProb;
	double m_minProb;
	std::vector<double> m_probs;
	unsigned int m_xPos;
	unsigned int m_yPos;
  bool m_invertColors;
};

}//namespace NICE

#endif

