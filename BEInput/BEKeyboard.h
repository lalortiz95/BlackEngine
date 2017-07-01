#pragma once

/// The engine's namespace.
namespace BlackEngine
{
	/// Definition of Keyboard class. It'll handle keyboard input events.
	class BEKeyboard
	{
	public:
		///Default constructor and destructor.
		BEKeyboard();
		~BEKeyboard();

		///This function initializes the class' variables.
		void Initialize();
		///Releases memory and deletes the member variables.
		void Destroy();


	};
}