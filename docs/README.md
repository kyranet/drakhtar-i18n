# Getting Started

## File Structure

The file structure is similar to that used in configuration systems across many
operative systems:

```python
# Your comment
FOO="Bar"
HELLO="World" # Inline comment
```

This generates the following structure when reading:

```javascript
Map(2) {
	"FOO" => StringContent[ "Bar" ],
	"HELLO" => StringContent[ "World" ]
}
```

As you can see, anything preceding a `#` becomes a comment and is ignored, as
well as all the key-values are exported and uses a `KEY="VALUE"` syntax.

### Variables

`drakhtar-i18n` supports variables out of the box, they use curly brackets
(`{}`) surrounding an integer number:

```python
HELLO="Hello {0}, nice to meet you!"
```

This tells the library `HELLO` is a language key with a variable, with the
default type of `string`, a such, if we call `Locale::format` with it, we will
get the following result:

```cpp
locale.format("HELLO", "Drakhtar");
// -> "Hello Drakhtar, nice to meet you!"
```

To break down what just happened, `Locale::format` is as method that takes a
variadic amount of arguments, those arguments are converted into a vector of
strings and then passed to the formatter, which inserts them in the correct
order.

Furthermore, you can also define different types, which are added next to the
argument's number, e.g. `{0i8}` defines that the first argument is of type
`int8_t`. If this type is not given, the default (`s`) is implied. The allowed
types are:

- `X`, `Xs` = `std::string`
- `Xb` = `boolean`
- `XiY` = `intY_t`
	- `Xi8` => `int8_t`
	- `Xi16` => `int16_t`
	- `Xi32` => `int32_t`
	- `Xi64` => `int64_t`
- `XuY` = `uintY_t`
	- `Xu8` => `uint8_t`
	- `Xu16` => `uint16_t`
	- `Xu32` => `uint32_t`
	- `Xu64` => `uint64_t`
- `XfY` = `floatY_t`
	- `Xf32` => `float32_t` / `float`
	- `Xf64` => `float64_t` / `double`

Locale-aware formatting is applied when formatting values different to strings
in different languages, for example `14000.43f` would be formatted as `14.000,43`
in `es-ES` and `14,000.43` in `en-US`.

So given the following string:

```python
HELLO="Hello {0}, I have been waiting you for {1i32} days!"
```

We would need to pass `Locale::format` both a `std::string` and an `int32_t`:

```cpp
locale.format("HELLO", "Drakhtar", 6100);
// -> "Hello Drakhtar, I have been waiting you for 6,100 days!"
```

## Folder Structure

```
/languages
  |- en-US
    |- .meta.txt
    |- your-file.txt
  |- es-ES
    |- .meta.txt
    |- your-file.txt
```

The `.meta.txt` files are injected by the library into the output binaries, and
contain the metadata information required for a correct format of the primitive
types.

To load the language files, you use the `load` method from `LocaleManager`,
which will then load all the files from a folder recursively if it exists,
throwing an error otherwise:

```cpp
manager.load("en-US");
```

You can also unload any other loaded locale using the `unload` method, and
access to a vector of loaded languages using the `loaded` method.

Furthermore, you can also list all the available locales by using
`LocaleManager::list`, which will return a map of the folder names and their
full name, in the example above:

```cpp
manager.list();
// Map(2) {
//   "en-US" => "English (United States)",
//   "es-ES" => "Español (España)"
// }
```

Which is useful particularly for making a language selector in your project.

At last, you can also auto-detect the user's preferred locale by using
`LocaleManager::getPreferred`, which returns a `Locale` object with the raw name,
the language name, and the country name.

## Namespaces

If you put files inside a folder, their names will be prefixed with the folder's
name, so if you define a key named `foo` inside `languages/en-US/misc/text.txt`,
the key would then be accessible at `misc/foo` and not with just `foo`.

If a key was already defined in a namespace, the behavior is that the library
will print a warning and override the existing key.

## Continue Reading

- [Fallbacks](./fallbacks.md)
- [Assets](./assets.md)
