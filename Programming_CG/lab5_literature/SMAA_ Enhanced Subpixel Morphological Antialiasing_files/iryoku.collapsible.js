/**
 * Collapsible plugin
 *
 * Copyright (c) 2010 Ramin Hossaini (www.ramin-hossaini.com)
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 *
 * Modified by Jorge Jimenez (www.iryoku.com)
 */

jQuery.collapsible = function(selector) {
    var baseId = 'collapsible_' + $(location).attr('pathname').substring(1).replace(/-/g, '_') + '_';
    var uniqueId = 0;
    var headers = $(selector).children('.header');

    headers.css('cursor', 'pointer');

    headers.click(function() {
        var header = $(this);
        var content = $(this).next();

        if (content.css('display') == 'none') {
            $.cookie(header.attr('id'), 'show');
            if (content.velocity)
                content.velocity('slideDown', { duration: 400 }).velocity('fadeIn', { duration: 400, queue: false });
            else
                content.slideDown(400).fadeIn(400, { queue: false });
            header.removeClass('expand').addClass('collapse');
        } else {
            $.cookie(header.attr('id'), 'hide');
            if (content.velocity)
                content.velocity('slideUp', { duration: 400 }).velocity('fadeOut', { duration: 400, queue: false });
            else
                content.slideUp(400).fadeOut(400, { queue: false });
            header.removeClass('collapse').addClass('expand');
        }
        return false;
    });

    $.each(headers, function() {
        var header = $(this);
        var content = $(this).next();

        header.attr('id', baseId + uniqueId);

        if (header.hasClass('collapsed')) {
            content.css("display", "none");
            header.removeClass('collapse').addClass('expand');
        } else {
            header.removeClass('expand').addClass('collapse');
        }

        if ($.cookie(header.attr('id')) == 'hide') {
            content.css("display", "none");
            header.removeClass('collapse').addClass('expand');
        } else if ( $.cookie(header.attr('id')) == 'show' ) {
            content.css("display", "block");
            header.removeClass('expand').addClass('collapse');
        }

        uniqueId++;
    });
};
