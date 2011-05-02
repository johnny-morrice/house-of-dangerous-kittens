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

desc "Test player movement"
task :pmove => [:clean, "work"] do
	debug "work/pmove", "test/pmove.c"
	sh "work/pmove"
end

desc "Build kitten path-finding test"
task :build_kitten => [:clean, "work"] do
	debug "work/kitten", "test/kittens.c"
end

desc "Test kitten path-finding"
task :kitten => [:build_kitten] do
	sh "work/kitten"
end

desc "Build dangerous kitten test"
task :build_danger => [:clean, "work"] do
	debug "work/danger", "test/danger.c"
end

desc "Test dangerous kittens"
task :danger => [:build_danger] do
	sh "work/danger"
end

desc "Build restarter test"
task :build_restart => [:clean, "work"] do
	debug "work/restart", "test/restart.c"
end

desc "Test restarter"
task :restart => [:build_restart] do
	sh "work/restart"
end

desc "Build a debug version of the game"
task :build_debug_game => [:clean, "work"] do
	debug "work/house", "src/main.c"
end

desc "Play a debug version of the game"
task :debug_game => :build_debug_game do
	sh "work/house"
end

desc "Build optimized version of the game"
task :build_game do
	compile "work/house", "-O2 -ffast-math", "src/main.c"
end

desc "Play optimized version of the game"
task :game => :build_game do
	sh "work/house"
end

desc "Word count"
task :words do
	sh "wc `find -regex '.+\\.\\(c\\|\\h\\)' ` | sort -n"
end
