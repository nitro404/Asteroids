using System;

namespace Asteroids {
	static class Program {
		static void Main(string[] args) {
			using(Asteroids game = new Asteroids()) {
				game.Run();
			}
		}
	}
}

