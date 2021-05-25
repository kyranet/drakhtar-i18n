# Assets

`drakhtar-i18n` includes a native way to load assets (fonts, images, textures,
etc) based on the locale and respecting [fallbacks](./fallbacks.md), which
allows developers to conditionally use them in an easy and convenient way.

For this task, we provide `LocaleManager::getPath`, which returns the path of
the directory.

So in this case, if we were looking for an asset named `images/logo.png`, and
the program's preferred locale is `es-ES`, with source fallback of `en-US`, the
library will try to find the file in the following order:

- `languages/es-ES/images/logo.png`
- `languages/es/images/logo.png`
- `languages/en-US/images/logo.png`
- `languages/en/images/logo.png`

Throwing an error if the asset could not be found.

Furthermore, to reduce the loading time in the application, an option can be
passed when initializing the library so it pre-loads the paths of all files when
loading a language folder, as well as the fallback one.
