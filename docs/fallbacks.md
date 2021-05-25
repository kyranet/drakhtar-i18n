# Fallback

Developers can also implement fallbacks of the kind `en-US` -> `en`, this allows
them to define most of the common keys in `en` and re-use them in any other
country, e.g. `en-GB`, `en-AU`, etc. The default behavior is that the library
will look for a fallback and load it if it exists, then override its keys with
the country-specific. As such, having this set-up:

```py
# en
HELLO="Hey, my name is {0}!"
LANGUAGE="And I am from an English-talking country!"
```

```py
# en-US
LANGUAGE="And I am from United States!"
```

```py
# en-GB
LANGUAGE="And I am from United Kingdom!"
COUNTRY="United Kingdom"
```

If you load those files, `en-US` will result on:

```javascript
Map(2) {
	"HELLO" => StringContent[ "Hey, my name is ", 0, "!" ],
	"LANGUAGE" => StringContent[ "And I am from United States!" ]
}
```

Similarly `en-GB`:

```javascript
Map(3) {
	"HELLO" => StringContent[ "Hey, my name is ", 0, "!" ],
	"LANGUAGE" => StringContent[ "And I am from United Kingdom!" ],
	"COUNTRY" => StringContent[ "United Kingdom" ]
}
```

This fallback mechanic is useful specially for reducing the amount of words to
translate, which reduces translation costs for the developers.

> This behavior is also present for script-specific locales, e.g. `ja-kata-JP`
(Japanese from Japan in Katakana) -> `ja-JP` (Japanese from Japan) -> `ja`
(Japanese) and `hi-latn-IN` (Hindi from India in Latin) -> `hi-IN` (Hindi from
India) -> `hi` (Hindi).
