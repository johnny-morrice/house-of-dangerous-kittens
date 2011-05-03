require "fileutils"

ENGINE = ["src/player.c", "src/screen.c",
	"src/level.c", "src/timetrack.c",
	"src/control.c", "src/zone.c",
	"src/input.c", "src/sprite.c",
	"src/draw.c", "src/directory.c",
	"src/entity.c", "src/fatal.c",
	"src/tiles.c", "src/kitten.c",
	"src/look.c", "src/cursor.c",
	"src/entity_set.c", "src/collide.c",
	"src/hud.c", "src/audio.c"]

def compile out, flags, *paths
	sh "gcc -o #{out} #{flags} -Wall `pkg-config --cflags --libs gobject-2.0` `pkg-config --cflags --libs sdl` -lSDL_image -lSDL_mixer -Iinclude #{ENGINE.join " "} #{paths.join " "}"
end

def debug out, *paths
	compile out, "-g", *paths
end

file "work" do
	FileUtils.mkdir "work"
end

desc "Clean tree"
task :clean do
	FileUtils.rm_rf "work"
end

desc "Build a debug version of the game"
task :debug => [:clean, "work"] do
	debug "work/kittensdbg", "src/main.c"
end

desc "Build optimized version of the game"
task :build => [:clean, "work"] do
	compile "work/kittens", "-O2 -ffast-math", "src/main.c"
end

desc "Play optimized version of the game"
task :play => :build do
	sh "work/kittens"
end

desc "Word count"
task :words do
	sh "wc `find -regex '.+\\.\\(c\\|\\h\\)' ` | sort -n"
end
