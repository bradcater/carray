require 'mkmf'

home_dir = `echo $HOME`.strip
dirs = [
  File.join(home_dir, 'include/glib-2.0'),
  File.join(home_dir, 'lib/glib-2.0/include'),
  File.join(home_dir, 'lib'),
]

dirs.each{|d| puts d}

extension_name = 'carray'
dir_config(extension_name)
dir_config('glib-2.0',
  # Include paths.
  dirs,
  # Library paths.
  dirs
)
if have_library("glib-2.0")
  create_makefile(extension_name)
else
  puts 'No glib support available.'
end
