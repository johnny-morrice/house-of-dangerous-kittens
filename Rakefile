require "fileutils"

ENGINE = ["src/player.c", "src/screen.c",
	"src/level.c", "src/timetrack.c",
	"src/control.c", "src/zone.c",
	"src/input.c", "src/sprite.c",
	"src/draw.c", "src/directory.c",
	"src/entity.c", "src/fatal.c"]

def compile out, flags, *paths
	sh "gcc -o #{out} #{flags} -Wall `pkg-config --cflags --libs gobject-2.0` `pkg-config --cflags --libs sdl` -lSDL_image -Iinclude #{ENGINE.join " "} #{paths.join " "}"
end

def debug out, *paths
	compile out, "-g", *paths
end

file "work" do
	FileUtils.mkdir "work"
end

desc "Clean tree"
task :clean do
	FileUtils.rm_r "work"
end

desc "Test player movement"
task :pmove => [:clean, "work"] do
	debug "work/pmove", "test/pmove.c"
	sh "work/pmove"
end
