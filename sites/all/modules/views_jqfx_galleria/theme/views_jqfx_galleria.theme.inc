<?php

/**
 * @file
 * Theme & preprocess functions for the Views jQFX: Galleria module.
 */

/**
 * @TODO.
 */
function template_preprocess_views_jqfx_galleria(&$vars) {
  $options = $vars['options']['views_jqfx_galleria'];
  $view = $vars['view'];

  // Get our image styles
  $main_style = $options['image']['main_style'];
  $thumb_style = $options['image']['thumbnails']['thumb_style'];
  $big_style = $options['image']['fullscreen']['fullscreen_style'];

  // @TODO
  // Get the field map settings
  // Proper namespace prefix needs to be returned
  // if it's field, node, entity, etc...
  if (!empty($options['fields']['image_field'])) {
    if (($options['fields']['image_field'] == 'title') || ($options['fields']['image_field'] == 'body')) {
      $image_field = "node_" . $options['fields']['image_field'];
      $image_node_field = TRUE;
    }
    else $image_field = "field_" . $options['fields']['image_field'];
  }
  else $image_field = NULL;

  // Title field
  if (!empty($options['fields']['title_field'])) {
    if (($options['fields']['title_field'] == 'title') || ($options['fields']['title_field'] == 'body')) {
      $title_field = "node_" . $options['fields']['title_field'];
      $title_node_field = TRUE;
    }
    else $title_field = "field_" . $options['fields']['title_field'];
  }

  // Description field
  if (!empty($options['fields']['desc_field'])) {
    if (($options['fields']['desc_field'] == 'title') || ($options['fields']['desc_field'] == 'body')) {
      $desc_field = "node_" . $options['fields']['desc_field'];
      $desc_node_field = TRUE;
    }
    else $desc_field = "field_" . $options['fields']['desc_field'];
  }

  // Link field
  if (!empty($options['fields']['link_field'])) {
    if (($options['fields']['link_field'] == 'title') || ($options['fields']['link_field'] == 'body')) {
      $link_field = "node_" . $options['fields']['link_field'];
      $link_node_field = TRUE;
    }
    else $link_field = "field_" . $options['fields']['link_field'];
  }

  // Layer title field
  if (!empty($options['fields']['layer_field_title'])) {
    if (($options['fields']['layer_field_title'] == 'title') || ($options['fields']['layer_field_title'] == 'body')) {
      $layer_title_field = "node_" . $options['fields']['layer_field_title'];
      $layer_title_node_field = TRUE;
    }
    else $layer_title_field = "field_" . $options['fields']['layer_field_title'];
  }

  // Layer text field
  if (!empty($options['fields']['layer_field_text'])) {
    if (($options['fields']['layer_field_text'] == 'title') || ($options['fields']['layer_field_text'] == 'body')) {
      $layer_text_field = "node_" . $options['fields']['layer_field_text'];
      $layer_text_node_field = TRUE;
    }
    else $layer_text_field = "field_" . $options['fields']['layer_field_text'];
  }

  // Find out if our link image field module is installed
  // And use its formatter if it is
//  if (module_exists('linkimagefield')) {
//    $formatter = 'linkimage_formatter';
//  }
//  else {
    $formatter = 'image_formatter';
//  }

  // @TODO
  // foreach loops need to be nested so that
  // proper field mapping data is returned for the image
  // whether it is coming from a single entity or
  // we are trying to pair fields with data from
  // multiple entities
  $slide = array();
  if ((!is_null($image_field)) && (!isset($image_node_field))) {
    foreach ($view->result as $rid) {
      foreach ($rid->{$image_field} as $iid => $image) {
        $image_uri = $image['raw']['uri'];

        $main_url = views_jqfx_galleria_main_image_url($main_style, $image_uri);

        $big_url = views_jqfx_galleria_big_image_url($big_style, $image_uri);

        if (!empty($big_url)) {
          $attr = array(
            'attributes' => array(
              'rel' => $big_url,
            )
          );
        }
        else $attr = array();

        $slide = array(
          '#theme' => $formatter,
          '#item' => $image['rendered']['#item'],
          '#image_style' => $thumb_style,
          '#path' => array(
            'path' => $main_url,
            'options' => $attr,
          ),
        );

        // Override default title
        if (!empty($title_field)) {
          if (isset($title_node_field)) {
            $slide['#item']['title'] = $rid->{$title_field};
          }
          elseif (!empty($rid->{$title_field}[$iid]['rendered']['#markup'])) {
            $slide['#item']['title'] = $rid->{$title_field}[$iid]['rendered']['#markup'];
          }
          else $slide['#item']['title'] = NULL;
        }

        // Override default description
        if (!empty($desc_field)) {
          if (isset($desc_node_field)) {
            $slide['#item']['alt'] = $rid->{$desc_field};
          }
          elseif (!empty($rid->{$desc_field}[$iid]['rendered']['#markup'])) {
            $slide['#item']['alt'] = $rid->{$desc_field}[$iid]['rendered']['#markup'];
          }
          else $slide['#item']['alt'] = NULL;
        }

        // Override default longdesc
        if (!empty($link_field)) {
          if (isset($link_node_field)) {
            $slide['#item']['longdesc'] = $rid->{$link_field};
          }
          elseif (!empty($rid->{$link_field}[$iid]['rendered']['#markup'])) {
            $slide['#item']['longdesc'] = $rid->{$link_field}[$iid]['rendered']['#markup'];
          }
          else $slide['#item']['longdesc'] = NULL;
        }

        // Get the info for the layer title
        if (!empty($layer_title_field)) {
          if (isset($layer_title_node_field)) {
            $html_title_layer = $rid->{$layer_title_field};
          }
          elseif (!empty($rid->{$layer_title_field}[$iid]['rendered']['#markup'])) {
            $html_title_layer = $rid->{$layer_title_field}[$iid]['rendered']['#markup'];
          }
        }

        // Get the info for the layer text
        if (!empty($layer_text_field)) {
          if (isset($layer_text_node_field)) {
            $html_text_layer = $rid->{$layer_text_field};
          }
          elseif (!empty($rid->{$layer_text_field}[$iid]['rendered']['#markup'])) {
            $html_text_layer = $rid->{$layer_text_field}[$iid]['rendered']['#markup'];
          }
        }

        // Create the full html layer
        if ((!empty($layer_title_field)) || (!empty($layer_text_field))) {
          if ((isset($html_title_layer)) || (isset($html_text_layer))) {
            if (isset($html_title_layer)) {
              $html_layer = '<h2>' . $html_title_layer . '</h2>';
              if (isset($html_text_layer)) {
                $html_layer .= $html_text_layer;
              }
            }
            else $html_layer = $html_text_layer;
          }
        }

        // Get the slide rendered from the image formatter
        $slide = drupal_render($slide);

        // Add the html layer to the rendered slide
        if (isset($html_layer)) {
          $slide .= "\n<div class='layer'><div>" . $html_layer . "</div></div>";
        }

        // All that to pass this
        $vars['content'][] = $slide;

        // Unset layer vars for next loop
        unset($html_title_layer);
        unset($html_text_layer);
        unset($html_layer);
      }  
    }
  }
  // @TODO
  // If a node element (title or body) is mapped to our images
  // we will need a completely different preprocess function.
  // For now just set as null
  else $vars['content'] = NULL;

  _views_jqfx_galleria_add_js($options, 'views-jqfx-galleria-images-' . $vars['id']);
}

/**
 * @TODO.
 */
function _views_jqfx_galleria_add_js($options, $id) {
  // Get the path to the plugin.
  $plugin_path = libraries_get_path('galleria');

  // Add the plugin js
  if ($options['advanced']['minify_js']) {
    drupal_add_js($plugin_path . '/galleria.min.js');
  }
  else drupal_add_js($plugin_path . '/galleria.js');

  // If the history option is chosen add its javascript
  if ($options['advanced']['history']) {
    drupal_add_js($plugin_path . '/plugins/galleria.history.js');
  }

  // Add the module css
  $module_path = drupal_get_path('module', 'views_jqfx_galleria');
  drupal_add_css($module_path . '/css/views_jqfx_galleria.css');

  // Get region the for loading Galleria javascript loadTheme and init functions
  $region = check_plain($options['advanced']['js_region']);

  // Build the Galleria loadTheme function and add it to the bottom of the page
  if (file_exists($plugin_path . '/themes/' . $options['theme'] . '/galleria.' . $options['theme'] . '.min.js')) {
    $theme_path = $plugin_path . '/themes/' . $options['theme'] . '/galleria.' . $options['theme'] . '.min.js';
  }
  elseif (file_exists($plugin_path . '/themes/' . $options['theme'] . '/galleria.' . $options['theme'] . '.js')) {
    $theme_path = $plugin_path . '/themes/' . $options['theme'] . '/galleria.' . $options['theme'] . '.js';
  }
  else $theme_path = $plugin_path . '/themes/classic/galleria.classic.js';

  $javascript = '(function ($) {Galleria.loadTheme("' . base_path() . $theme_path . '");})(jQuery);';
  drupal_add_js($javascript, array('type' => 'inline', 'scope' => $region, 'weight' => 4));

  //@TODO
  // Organize and combine settings where possible
  //
  // Get an array of settings that we will pass to the Galleria
  $settings = array(
    'height'                  => ($options['height'] == 'auto') ? 'auto' : (int) $options['height'],
    'width'                   => ($options['width'] == 'auto') ? 'auto' : (int) $options['width'],
    // Display
    'show'                    => ($options['display']['show'] === 'false') ? FALSE : (int) $options['display']['show'],
    'showCounter'             => (bool) $options['display']['show_counter'],
    'showImagenav'            => (bool) $options['display']['show_imagenav'],
    'showInfo'                => (bool) $options['display']['show_info'],
    // Behavoir
    'autoplay'                => (int) $options['behavior']['autoplay'],
    'clicknext'               => (bool) $options['behavior']['clicknext'],
    'layerFollow'             => (bool) $options['behavior']['layer_follow'],
    'pauseOnInteraction'      => (bool) $options['behavior']['pause_on_interaction'],
    'popupLinks'              => (bool) $options['behavior']['popup_links'],
    'preload'                 => ($options['behavior']['preload'] == 'auto') ? 'auto' : (int) $options['behavior']['preload'],
    'queue'                   => (bool) $options['behavior']['queue'],
    'swipe'                   => (bool) $options['behavior']['swipe'],
    // Carousel
    'carousel'                => (bool) $options['behavior']['carousel']['carousel'],
    'carouselFollow'          => (bool) $options['behavior']['carousel']['carousel_follow'],
    'carouselSpeed'           => (int) $options['behavior']['carousel']['carousel_speed'],
    'carouselSteps'           => ($options['behavior']['carousel']['carousel_steps'] == 'auto') ? 'auto' : (int) $options['behavior']['carousel']['carousel_steps'],
    // Idle mode
    'idleMode'                => (bool) $options['behavior']['idle_mode']['idle_mode'],
    'idleSpeed'               => (int) $options['behavior']['idle_mode']['idle_speed'],
    'idleTime'                => (int) $options['behavior']['idle_mode']['idle_time'],
    // Image pan
    'imagePan'                => (bool) $options['behavior']['image_pan']['image_pan'],
    'imagePanSmoothness'      => (int) $options['behavior']['image_pan']['image_pan_smoothness'],
    // Transition
    'transition'              => $options['transition']['transition'],
    'transitionInitial'       => $options['transition']['transition_initial'],
    'transitionSpeed'         => (int) $options['transition']['transition_speed'],
    // Image
    'imageMargin'             => (int) $options['image']['image_margin'],
    'imagePosition'           => check_plain($options['image']['image_position']),
    'minScaleRatio'           => (int) $options['image']['min_scale_ratio'],
    'maxScaleRatio'           => (int) $options['image']['max_scale_ratio'],
    // Thumbnails
    'thumbFit'                => (bool) $options['image']['thumbnails']['thumb_fit'],
    'thumbMargin'             => (int) $options['image']['thumbnails']['thumb_margin'],
    // Fullscreen
    'fullscreenDoubleTap'     => (bool) $options['image']['fullscreen']['fullscreen_double_tap'],
    // Lightbox
    'lightbox'                => (bool) $options['lightbox']['lightbox'],
    'lightboxFadeSpeed'       => (int) $options['lightbox']['lightbox_fade_speed'],
    'lightboxTransitionSpeed' => (int) $options['lightbox']['lightbox_transition_speed'],
    'overlayBackground'       => check_plain($options['lightbox']['overlay_background']),
    'overlayOpacity'          => (float) $options['lightbox']['overlay_opacity'],
    // Advanced
    'debug'                   => (bool) $options['advanced']['debug'],
    'keepSource'              => (bool) $options['advanced']['keep_source'],
  );

  // Thumbnails is empty, numbers or boolean.
  if ($options['image']['thumbnails']['thumbnails'] == 'empty') {
    $settings['thumbnails'] = 'empty';
  }
  elseif ($options['image']['thumbnails']['thumbnails'] == 'numbers') {
    $settings['thumbnails'] = 'numbers';
  }
  else $settings['thumbnails'] = (bool) $options['image']['thumbnails']['thumbnails'];

  // @TODO
  // Combine the following crop statements
  //
  // Image crop is true, false or by height or width.
  if ($options['image']['image_crop'] == 'width') {
    $settings['imageCrop'] = 'width';
  }
  elseif ($options['image']['image_crop'] == 'height') {
    $settings['imageCrop'] = 'height';
  }
  else $settings['imageCrop'] = (bool) $options['image']['image_crop'];

  // Thumb crop is true, false or by height or width.
  if ($options['image']['thumbnails']['thumb_crop'] == 'width') {
    $settings['thumbCrop'] = 'width';
  }
  elseif ($options['image']['thumbnails']['thumb_crop'] == 'height') {
    $settings['thumbCrop'] = 'height';
  }
  else $settings['thumbCrop'] = (bool) $options['image']['thumbnails']['thumb_crop'];

  // Fullscreen crop is true, false or by height or width.
  if ($options['image']['fullscreen']['fullscreen_crop'] == 'width') {
    $settings['fullscreenCrop'] = 'width';
  }
  elseif ($options['image']['fullscreen']['fullscreen_crop'] == 'height') {
    $settings['fullscreenCrop'] = 'height';
  }
  else $settings['fullscreenCrop'] = (bool) $options['image']['fullscreen']['fullscreen_crop'];

  // @TODO
  // Combine these
  //
  // These settings will break the Galleria if they are passed empty
  // This checks to be sure they are set before being added to
  // the settings array
  if ($options['advanced']['data_selector']) {
    $settings['dataSelector'] = $options['advanced']['data_selector'];
  }
  if ($options['advanced']['data_source']) {
    $settings['dataSource'] = $options['advanced']['data_source'];
  }
  if ($options['advanced']['data_config']) {
    $settings['dataConfig'] = $options['advanced']['data_config'];
  }
  if ($options['advanced']['extend']) {
    $settings['extend'] = $options['advanced']['extend'];
  }

  // If dataConfig was not manually entered and html layer fields
  // are present we will pass a function to create our html layers
  if ((!empty($options['fields']['layer_field_title'])) || (!empty($options['fields']['layer_field_title']))) {
    if (!isset($settings['dataConfig']))
      $settings['dataConfig'] = "function(img) { return { layer: $(img).parent().next('.layer').html() } }";
  }

  // Pass the javascript settings.
  drupal_add_js(array('viewsJqfxGalleria' => array($id => $settings)), 'setting');

  // Add the module javascript with the init function at bottom of page
  drupal_add_js($module_path . '/js/views_jqfx_galleria.js', array('scope' => $region, 'weight' => 5));
}

/**
 * Returns the url for the main galleria stage image.
 */
function views_jqfx_galleria_main_image_url($main_style, $image_uri) {
  if (!empty($main_style)) {
    $main_url = image_style_url($main_style, $image_uri);
  }
  else $main_url = file_create_url($image_uri);
  return $main_url;
}

/**
 * Returns the url for the galleria lightbox and fullscreen modes.
 */
function views_jqfx_galleria_big_image_url($big_style, $image_uri) {
  if (empty($big_style)) {
    $big_url = file_create_url($image_uri);
  }
  elseif ((!empty($big_style)) && ($big_style != $main_style)) {
    $big_url = image_style_url($big_style, $image_uri);
  }
  else $big_url = '';
  return $big_url;
}
