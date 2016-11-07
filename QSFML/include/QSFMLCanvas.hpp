/* =========================================================== *
 * QSFML (c) Kamil Koczurek | koczurekk@gmail.com			  *
 * GNU GPL v3 License http://www.gnu.org/licenses/gpl-3.0.html *
 * =========================================================== */

//! @file
//! QSFMLWidget declaration file

/*! \mainpage QSFML
 *
 * \section About
 *
 * Library that integrates SFML 2.3.x; 2.4.1+ (2.4.0 causes a X11-related problem) and Qt 5, includes event handling, universal types, useful functions (eg. key code converter) etc.
 *
 * \section Installation
 * \subsection Compile
 *   - git clone https://github.com/KoczurekK/QSFML.git
 *   - cd QSFML/QSFML/src
 *   - qmake
 *   - make
 * \subsection Deb packages
 * Download .deb packages from leatest github release and install using dpkg/apt etc.
 *
 * \section Usage
 * All header files are in QSFML subdirectory, include useful ones and remember to link with -lQSFML.
 *
 * \section Origins
 * Basic code, on top of which im writing QSFML, was created by "jueves", you can find original post <a href=" http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html">here</a>
 */

#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <qdebug.h>
#include <QWidget>
#include <QTimer>

//! \brief Namespace containing all qsf classes and methods.
namespace qsf {
	//! \class QSFMLWidget
	//! \brief Qt widget used as SFML window
	//!
	//! This class inherits sf::InputStream and sf::RenderWindow, so sometimes you have to specify with methods you want to use as some of them (eg. setSize) coexist in both.
	//! You can use this class to move your SFML apps into Qt widget without too big changes in code.
	class QSFMLWidget
	: public QWidget,
	public sf::RenderWindow {
	public:
		//! \brief Default constructor
		//!
		//! \param [in] parent – Parent widget
		//! \param [in] Position – Defines QSFMLWidget position
		//! \param [in] Size – Defines QSFMLWidget size
		//! \param [in] FrameTime – OnUpdate() call interval
		//!
		//! Sets widget Qt attributes, sets proper size and position, sets up frame timer (requred to measure delta time)
		//! and prepares QTimer calling OnUpdate() every FrameTime miliseconds.
		explicit QSFMLWidget(QWidget *parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 7); //Defauld frame time should give about 144 FPS

		//! \brief Destructor
		//!
		//! Calls derived classes destructors due to virtual keyword and then OnDestroy() method of exactly this class, not derived one.
		virtual ~QSFMLWidget();

		//! \brief Basic widget init
		//!
		//! \param [in] (noname) – not used due to class structure
		//!
		//!   - Connects sf::RenderWindow to instance defined by *this;
		//!   - Calls OnInit();
		//!   - Connects QTimer to repaint() slot and starts it.
		virtual void showEvent(QShowEvent*);

		//! \brief Does nothing
		//!
		//! \return 0
		//!
		//! Exists just to fit Qt requirements
		virtual QPaintEngine* paintEngine() const;

		//! \brief Manages OnUpdate()
		//!
		//! \param [in] (noname) – not used due to class structure
		//!
		//!   - Measures delta time and saves it to _frameTime;
		//!	  - Calls OnUpdate();
		//!   - Calls sf::RenderWindow::display().
		virtual void paintEvent(QPaintEvent*);

		//! \brief Called after creating sf::RenderWindow
		virtual void OnInit();

		//! \brief Called every frame
		virtual void OnUpdate();

		//! \brief Called after destroying widget
		//!
		//! It needs to be implemented semi-explictly to work.
		//! OnDestroy() is called by destructor, so only derived class destructor can do so.
		//! To keep the code clean, use OnDestroy() to clean SFML-related things and destructor to free resources etc.
		//!
		//! Use similar code to enable OnDestroy():
		//! \code{.cpp}
		//! class SampleClass
		//! : public qsf::QSFMLWidget {
		//!		// ...
		//!		~SampleClass() {
		//!			OnDestroy();
		//!			// ...
		//!		}
		//!		// ...
		//!	};
		//! \endcode
		virtual void OnDestroy();

		bool pollEvent(sf::Event & ev);

		/* =============== *
		 * EVENTS HANDLING *
		 * =============== */
		//Mouse buttons
		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);

		//Mouse wheel
		void wheelEvent(QWheelEvent *e);

		//Keyboard
		void keyPressEvent(QKeyEvent *e);
		void keyReleaseEvent(QKeyEvent *e);

		//Resize event
		void resizeEvent(QResizeEvent *event);

	private:
		bool _initialized;
		QTimer refreshTimer;
		sf::Time _frameTime;
		sf::Clock frameClock;

	protected:
		const bool & initialized = _initialized;
		const sf::Time & frameTime = _frameTime;

		void pushEvent(sf::Event & ev);
		std::vector<sf::Event> SfEvents;
	};
}
#endif // QSMLCANVAS_H
