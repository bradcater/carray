require 'mkmf'

extension_name = 'carray'
dir_config(extension_name)
dir_config('glib-2.0',
  # Include paths.
  %w{/usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include},
  # Library paths.
  %w{/usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include})
if have_library("glib-2.0")
  create_makefile(extension_name)
else
  puts 'No glib support available.'
end
