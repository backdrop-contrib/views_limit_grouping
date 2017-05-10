# Views Grouping Row Limit

This is a basic Views style plugin that allows for a limit on the number of rows
displayed within a grouping field. So, for instance, if you have a view that
outputs the following:

```
Grouping Field 1
 - Row 1
 - Row 2
 - Row 3
 - Row 4
 - Row 5

Grouping Field 2
 - Row 1
 - Row 2
 - Row 3
 ```

there is currently no way using Views to only show the first two rows under each
grouping field without painstakingly making several different displays. That's
where this module comes in.

To use this module, simply change the style plugin for your view to the 
"Grouping Field (with Limit)" option. You will then be presented with options 
to choose your limit and offset (the offset just controls what row to start on, 
e.g. an offset of 1 would omit the first row from each grouping field). Please 
note that in order for this to take effect, you must set your row limit on the 
actual view to Unlimited.

## Usage

Please use the [Wiki](https://github.com/backdrop-contrib/views_limit_grouping/wiki) 
to read more and contribute documentation.

## Issues

Bugs and Feature requests should be reported in the 
[Issue Queue](https://github.com/backdrop-contrib/views_limit_grouping/issues)

## Current Maintainers

 - [Laryn Kragt Bakker](https://github.com/laryn) - [CEDC.org](https://cedc.org)

## Credits

 - Ported to Backdrop CMS by [Laryn Kragt Bakker](https://github.com/laryn) - [CEDC.org](https://cedc.org).
 - Current maintainers for the Drupal module: [theunraveler](https://www.drupal.org/u/theunraveler). 
 - Originally sponsored by [August Ash, Inc.](http://augustash.com/).

## License

This project is GPL v2 software. See the [LICENSE.txt](https://github.com/backdrop-contrib/views_limit_grouping/blob/1.x-1.x/LICENSE.txt) 
file in this directory for complete text.