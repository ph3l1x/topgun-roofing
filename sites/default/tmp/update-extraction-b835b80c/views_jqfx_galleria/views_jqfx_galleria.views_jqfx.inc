<?php

/**
 * @file
 * The default options available with Views jQFX: galleria.
 */

/**
 * Implements hook_views_jqfx_jqfx_types().
 */
function views_jqfx_galleria_views_jqfx_jqfx_types() {
  $options = array(
    'views_jqfx_galleria' => t('Galleria'),
  );
  return $options;
}

function views_jqfx_galleria_views_jqfx_option_definition() {
  $options['views_jqfx_galleria'] = array(
    'contains' => array(
      'theme'                     => array('default' => 'classic'),
      'height'                    => array('default' => 400),
      'width'                     => array('default' => 600),
      // Field Map
      'fields'                    => array(
        'contains'                  => array(
          'image_field'               => array('default' => 'image'),
          'title_field'               => array('default' => ''),
          'desc_field'                => array('default' => ''),
          'link_field'                => array('default' => ''),
          'layer_field_title'         => array('default' => ''),
          'layer_field_text'          => array('default' => ''),
        ),
      ),
      // Display
      'display'                   => array(
        'contains'                  => array(
          'show'                      => array('default' => 0),
          'show_counter'              => array('default' => TRUE),
          'show_imagenav'             => array('default' => TRUE),
          'show_info'                 => array('default' => TRUE),
        ),
      ),
      // Behavior
      'behavior'                  => array(
        'contains'                  => array(
          'autoplay'                  => array('default' => FALSE),
          'clicknext'                 => array('default' => FALSE),
          'layer_follow'              => array('default' => TRUE),
          'pause_on_interaction'      => array('default' => TRUE),
          'popup_links'               => array('default' => FALSE),
          'preload'                   => array('default' => 2),
          'queue'                     => array('default' => TRUE),
          'swipe'                     => array('default' => TRUE),
          // Carousel
          'carousel'                  => array(
            'contains'                  => array(
              'carousel'                  => array('default' => TRUE),
              'carousel_follow'           => array('default' => TRUE),
              'carousel_speed'            => array('default' => 200),
              'carousel_steps'            => array('default' => 'auto'),
            ),
          ),
          // Idle mode
          'idle_mode'                 => array(
            'contains'                  => array(
              'idle_mode'                 => array('default' => TRUE),
              'idle_speed'                => array('default' => 200),
              'idle_time'                 => array('default' => 3000),
            ),
          ),
          // Image pan
          'image_pan'                 => array(
            'contains'                  => array(
              'image_pan'                 => array('default' => FALSE),
              'image_pan_smoothness'      => array('default' => 12),
            ),
          ),
        ),
      ),
      // Transition
      'transition'                => array(
        'contains'                  => array(
          'transition'                => array('default' => 'fade'),
          'transition_initial'        => array('default' => ''),
          'transition_speed'          => array('default' => 400),
          'easing'                    => array('default' => 'galleria'),
        ),
      ),
      // Image options
      'image'                     => array(
        'contains'                  => array(
          'main_style'                => array('default' => 'large'),
          'image_crop'                => array('default' => FALSE),
          'image_margin'              => array('default' => 0),
          'image_position'            => array('default' => 'center'),
          'max_scale_ratio'           => array('default' => ''),
          'min_scale_ratio'           => array('default' => ''),
          // thumbnails
          'thumbnails'                => array(
            'contains'                  => array(
              'thumbnails'                => array('default' => TRUE),
              'thumb_style'               => array('default' => 'thumbnail'),
              'thumb_crop'                => array('default' => TRUE),
              'thumb_fit'                 => array('default' => TRUE),
              'thumb_margin'              => array('default' => 0),
            ),
          ),
          // fullscreen
          'fullscreen'                => array(
            'contains'                  => array(
              'fullscreen_style'          => array('default' => ''),
              'fullscreen_crop'           => array('default' => TRUE),
              'fullscreen_double_tap'     => array('default' => TRUE),
            ),
          ),
        ),
      ),
      // Lightbox options
      'lightbox'                  => array(
        'contains'                  => array(
          'lightbox'                  => array('default' => FALSE),
          'lightbox_fade_speed'       => array('default' => 200),
          'lightbox_transition_speed' => array('default' => 200),
          'overlay_background'        => array('default' => '#0b0b0b'),
          'overlay_opacity'           => array('default' => 0.85),
        ),
      ),
      // Advanced options
      'advanced'                  => array(
        'contains'                  => array(
          'debug'                     => array('default' => FALSE),
          'minify_js'                 => array('default' => FALSE),
          'js_region'                 => array('default' => 'footer'),
          'history'                   => array('default' => FALSE),
          'keep_source'               => array('default' => FALSE),
          'data_selector'             => array('default' => NULL),
          'data_source'               => array('default' => NULL),
          'data_config'               => array('default' => NULL),
          'extend'                    => array('default' => NULL),
        ),
      ),
    ),
  );
  return $options;
}

/**
 * Implements hook_views_jqfx_views_jqfx_type_form().
 */
function views_jqfx_galleria_views_jqfx_jqfx_type_form(&$form, &$form_state, &$view) {
  ctools_include('dependent');
  if (!file_exists(libraries_get_path('galleria') . '/galleria.js')) {
    $form['views_jqfx_galleria']['no_galleria_js'] = array(
      '#markup' => '<div style="color: red">' . t('You need to download the Galleria plugin and copy it to your libraries folder (usually sites/all/libraries). You can find the plugin at !url. Be sure the version number has been removed from the %galleria.js and %galleria.min.js files.', array('!url' => l(t('http://galleria.aino.se', array(), array('langcode' => 'en')), 'http://galleria.aino.se', array('attributes' => array('target' => '_blank'))), '%galleria.js' => 'galleria.js', '%galleria.min.js' => 'galleria.min.js'), array('langcode' => 'en')) . '</div>',
    );
  }

  $themes = views_jqfx_galleria_get_themes();

  $form['views_jqfx_galleria']['theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#description' => t('Galleria theme to load on display. To add additional themes simply copy them to your libraries/galleria/themes/ folder.'),
    '#default_value' => $view->options['views_jqfx_galleria']['theme'],
    '#options' => $themes,
  );

  $form['views_jqfx_galleria']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('This will set a height to the gallery. If you set this to %auto and no CSS height is found, Galleria will try to automatically add a 16/9 ratio as a fallback. With some themes if this is left to %auto the Galleria will not load.', array('%auto' => 'auto')),
    '#default_value' => $view->options['views_jqfx_galleria']['height'],
  );

  $form['views_jqfx_galleria']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('This will set a width to the gallery. If you set this to %auto and no CSS height is found, Galleria will try to automatically add a 16/9 ratio as a fallback.', array('%auto' => 'auto')),
    '#default_value' => $view->options['views_jqfx_galleria']['width'],
  );

  // Field mapping fieldset
  $form['views_jqfx_galleria']['fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field mapping'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $fields = array();
  foreach ($view->display->handler->get_handlers('field') as $field => $handler) {
    if ($label = $handler->label()) {
      $fields[$field] = $label;
    }
    else {
      $fields[$field] = $handler->ui_name();
    }
  }

  $form['views_jqfx_galleria']['fields']['image_field'] = array(
    '#type' => 'select',
    '#title' => t('Image field'),
    '#description' => t("Select the field to use for your galleria images."),
    '#default_value' => $view->options['views_jqfx_galleria']['fields']['image_field'],
    '#options' => $fields,
  );

  $form['views_jqfx_galleria']['fields']['title_field'] = array(
    '#type' => 'select',
    '#title' => t('Title'),
    '#description' => t("Select a field to use for your image titles or use the default image %title attribute.", array('%title' => 'title')),
    '#default_value' => $view->options['views_jqfx_galleria']['fields']['title_field'],
    '#options' => array_merge(array('' => t('Image title attribute (default)')), $fields),
  );

  $form['views_jqfx_galleria']['fields']['desc_field'] = array(
    '#type' => 'select',
    '#title' => t('Description'),
    '#description' => t("Select a field to use for your image descriptions or use the default image %alt attribute.", array('%alt' => 'alt')),
    '#default_value' => $view->options['views_jqfx_galleria']['fields']['desc_field'],
    '#options' => array_merge(array('' => t('Image alt attribute (default)')), $fields),
  );

  $form['views_jqfx_galleria']['fields']['link_field'] = array(
    '#type' => 'select',
    '#title' => t('Link'),
    '#description' => t("Select a field to use for your image links or use the default image %longdesc attribute.", array('%longdesc' => 'longdesc')),
    '#default_value' => $view->options['views_jqfx_galleria']['fields']['link_field'],
    '#options' => array_merge(array('' => t('Image longdesc attribute (default)')), $fields),
  );

  $form['views_jqfx_galleria']['fields']['layer_field_title'] = array(
    '#type' => 'select',
    '#title' => t('HTML layer title'),
    '#description' => t("A field to use for the title of a layer of HTML that will be displayed on top of the image. This field automatically gets wrapped in h2 tags. Additional markup is limited only by your html filter and/or field type."),
    '#default_value' => $view->options['views_jqfx_galleria']['fields']['layer_field_title'],
    '#options' => array_merge(array('' => t('Not set')), $fields),
  );

  $form['views_jqfx_galleria']['fields']['layer_field_text'] = array(
    '#type' => 'select',
    '#title' => t('HTML layer text'),
    '#description' => t("A field to use for the text of a layer of HTML that will be displayed on top of the image. Markup is limited only by your html filter and/or field type."),
    '#default_value' => $view->options['views_jqfx_galleria']['fields']['layer_field_text'],
    '#options' => array_merge(array('' => t('Not set')), $fields),
  );

  // Images fieldset
  $form['views_jqfx_galleria']['image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $styles = array();
    foreach (image_styles() as $p) {
    $styles[$p['name']] = $p['name'];
  }
  $styles = array_merge(array('' => t('None (original image)')), $styles);

  $form['views_jqfx_galleria']['image']['main_style'] = array(
    '#type' => 'select',
    '#title' => t('Main image style'),
    '#description' => t('Select an image style for the main galleria stage.'),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['main_style'],
    '#options' => $styles,
  );
  
  $crop = array(
    FALSE => t('False'),
    TRUE => t('True'),
    'width' => t('Width'),
    'height' => t('Height'),
  );

  $form['views_jqfx_galleria']['image']['image_crop'] = array(
    '#type' => 'select',
    '#title' => t('Image scale/crop'),
    '#description' => t('If %true, all images will be scaled to fill the entire stage, centered and cropped. You can also scale images by either height or width. Otherwise, they will scale down so the entire image fits.', array('%true' => 'true')),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['image_crop'],
    '#options' => $crop,
  );

  $form['views_jqfx_galleria']['image']['image_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Image margin'),
    '#description' => t('Sets a margin between the image and stage. Specify the number of pixels.'),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['image_margin'],
  );

  $form['views_jqfx_galleria']['image']['image_position'] = array(
    '#type' => 'textfield',
    '#title' => t('Image position'),
    '#description' => t("Positions the main image. Works like the CSS background-position property; i.e., 'top right' or '20% 100%'. You can use keywords, percents or pixels. The first value is the horizontal position and the second is the vertical. Read more at !read_more.", array('!read_more' => l(t('http://www.w3.org/TR/REC-CSS1/#background-position', array(), array('langcode' => 'en')), 'http://www.w3.org/TR/REC-CSS1/#background-position', array('attributes' => array('target' => '_blank')))), array('langcode' => 'en')),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['image_position'],
  );

  $form['views_jqfx_galleria']['image']['max_scale_ratio'] = array(
    '#type' => 'textfield',
    '#title' => t('Max scale ratio'),
    '#description' => t("Sets the maximum scale ratio for images. If you don't want Galleria to upscale any images, set this to 1. Leaving it blank will allow any scaling of the images."),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['max_scale_ratio'],
  );

  $form['views_jqfx_galleria']['image']['min_scale_ratio'] = array(
    '#type' => 'textfield',
    '#title' => t('Min scale ratio'),
    '#description' => t("Sets the minimum scale ratio for images. If you don't want Galleria to downscale any images, set this to 1. Leaving it blank will allow any scaling of the images."),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['min_scale_ratio'],
  );

  // Thumbnails fieldset
  $form['views_jqfx_galleria']['image']['thumbnails'] = array(
    '#type' => 'fieldset',
    '#title' => t('Thumbnail options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $options = array(
    FALSE => t('False'),
    TRUE => t('True'),
    'empty' => t('Empty'),
    'numbers' => t('Numbers'),
  );

  $form['views_jqfx_galleria']['image']['thumbnails']['thumbnails'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnails'),
    '#description' => t("Sets the creation of thumbnails. If %false, Galleria will not create thumbnails and no carousel. If you set this to %empty, Galleria will create empty spans with the className img instead of thumbnails. If you set this to %numbers, Galleria will create empty spans with numbers instead of thumbnails.", array('%false' => 'false', '%empty' => 'empty', '%numbers' => 'numbers')),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['thumbnails']['thumbnails'],
    '#options' => $options,
  );

  $form['views_jqfx_galleria']['image']['thumbnails']['thumb_style'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnail image style'),
    '#description' => t('Select an image style for the galleria thumbnails.'),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['thumbnails']['thumb_style'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-image-thumbnails-thumbnails' => array(1)),
    '#options' => $styles,
  );

  $form['views_jqfx_galleria']['image']['thumbnails']['thumb_crop'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnail scale/crop'),
    '#description' => t("Same as %image_crop, but for thumbnails.", array('%image_crop' => t('Image crop'))),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['thumbnails']['thumb_crop'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-image-thumbnails-thumbnails' => array(1)),
    '#options' => $crop,
  );

  $form['views_jqfx_galleria']['image']['thumbnails']['thumb_fit'] = array(
    '#type' => 'select',
    '#title' => t('Thumb fit'),
    '#description' => t("If this is enabled, all thumbnail containers will be shrinked to fit the actual thumbnail size. This is useful if you have thumbnails of various sizes and will then float nicely side-by-side.This is only relevant if thumb_crop is set to anything else but 'true'.If you want all thumbnails to fit inside a container with predefined width & height, set this to 'false'."),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['thumbnails']['thumb_fit'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-image-thumbnails-thumbnails' => array(1)),
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['image']['thumbnails']['thumb_margin'] = array(
    '#type' => 'textfield',
    '#title' => t('Thumb margin'),
    '#description' => t("Same as %image_margin, but for thumbnails.", array('%image_margin' => t('Image margin'))),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['thumbnails']['thumb_margin'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-image-thumbnails-thumbnails' => array(1)),
  );

  // Fullscreen fieldset
  $form['views_jqfx_galleria']['image']['fullscreen'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fullscreen options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['views_jqfx_galleria']['image']['fullscreen']['fullscreen_style'] = array(
    '#type' => 'select',
    '#title' => t('Fullscreen image style'),
    '#description' => t('Select an image style for galleria fullscreen mode.'),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['fullscreen']['fullscreen_style'],
    '#options' => $styles,
  );

  $form['views_jqfx_galleria']['image']['fullscreen']['fullscreen_crop'] = array(
    '#type' => 'select',
    '#title' => t('Fullscreen scale/crop'),
    '#description' => t("Same as %image_crop, but for fullscreen.", array('%image_crop' => t('Image crop'))),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['fullscreen']['fullscreen_crop'],
    '#options' => $crop,
  );

  $form['views_jqfx_galleria']['image']['fullscreen']['fullscreen_double_tap'] = array(
    '#type' => 'select',
    '#title' => t('Fullscreen double tap.'),
    '#description' => t('This options listens for the double-tap event on touch devices and toggle fullscreen mode if it happens.'),
    '#default_value' => $view->options['views_jqfx_galleria']['image']['fullscreen']['fullscreen_double_tap'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  // Display fieldset
  $form['views_jqfx_galleria']['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $show = drupal_map_assoc(array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
  $show = array_merge(array('false' => t('False')), $show);

  $form['views_jqfx_galleria']['display']['show'] = array(
    '#type' => 'select',
    '#title' => t('Show'),
    '#description' => t("This defines what image index to show at first (zero index). If you use the history plugin, a permalink will override this number. For the %folio theme set this to %false.", array('%folio' => 'folio', '%false' => 'false'), array('langcode' => 'en')),
    '#default_value' => $view->options['views_jqfx_galleria']['display']['show'],
    '#options' => $show,
  );

  $form['views_jqfx_galleria']['display']['show_counter'] = array(
    '#type' => 'select',
    '#title' => t('Counter'),
    '#description' => t('%Disable if you do not wish to display the counter.', array('%Disable' => 'Disable')),
    '#default_value' => $view->options['views_jqfx_galleria']['display']['show_counter'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['display']['show_imagenav'] = array(
    '#type' => 'select',
    '#title' => t('Image navigation'),
    '#description' => t('%Disable if you do not wish to display the image navigation (next/prev arrows).', array('%Disable' => 'Disable')),
    '#default_value' => $view->options['views_jqfx_galleria']['display']['show_imagenav'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['display']['show_info'] = array(
    '#type' => 'select',
    '#title' => t('Image captions'),
    '#description' => t('%Disable if you do not wish to display the captions.', array('%Disable' => 'Disable')),
    '#default_value' => $view->options['views_jqfx_galleria']['display']['show_info'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  // Behavior fieldset
  $form['views_jqfx_galleria']['behavior'] = array(
    '#type' => 'fieldset',
    '#title' => t('Behavior options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $autoplay = drupal_map_assoc(array(0, 200, 400, 600, 800, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 4000, 5000, 7500, 10000));

  $form['views_jqfx_galleria']['behavior']['autoplay'] = array(
    '#type' => 'select',
    '#title' => t('Autoplay'),
    '#description' => t('If you set this to any number, f.ex 4000, it will start playing with that interval (in milliseconds). Set to zero to %disable.', array('%disable' => 'disable')),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['autoplay'],
    '#options' => $autoplay,
  );

  $form['views_jqfx_galleria']['behavior']['clicknext'] = array(
    '#type' => 'select',
    '#title' => t('Click next'),
    '#description' => t('Click the image to navigate to next item.'),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['clicknext'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['behavior']['layer_follow'] = array(
    '#type' => 'select',
    '#title' => t('Layer follow'),
    '#description' => t('By default, the layer follows the image size on the stage, even if crop is set. This means that the HTML layer will stretch according to the active image. If you want the layer to fill the stage regardless of cropping settings, set this to false.'),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['layer_follow'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['behavior']['pause_on_interaction'] = array(
    '#type' => 'select',
    '#title' => t('Pause on interaction'),
    '#description' => t('During playback, Galleria will stop the playback if the user presses thumbnails or any other navigational links. If you dont want this behaviour, set this option to %false.', array('%false' => 'false')),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['pause_on_interaction'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['behavior']['popup_links'] = array(
    '#type' => 'select',
    '#title' => t('Popup links'),
    '#description' => t('This will cause any image links to open in a new window.'),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['popup_links'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $preload = drupal_map_assoc(array('all', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

  $form['views_jqfx_galleria']['behavior']['preload'] = array(
    '#type' => 'select',
    '#title' => t('Preload'),
    '#description' => t("Defines how many images Galleria should preload in advance. Please note that this only applies when you are using separate thumbnail files. Galleria always cache all preloaded images. <ul><li>%2 preloads the next 2 images in line.</li><li>%all forces Galleria to start preloading all images. This may slow down client.</li><li>%0 will not preload any images</li></ul>", array('%2' => '2', '%all' => 'all', '%0' => '0')),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['preload'],
    '#options' => $preload,
  );

  $form['views_jqfx_galleria']['behavior']['queue'] = array(
    '#type' => 'select',
    '#title' => t('Queue'),
    '#description' => t("Galleria queues all activation clicks (next/prev & thumbnails). You can see this effect when, for example, clicking %next many times. Disable if you don't want Galleria to queue.", array('%next' => t('next'))),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['queue'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['behavior']['swipe'] = array(
    '#type' => 'select',
    '#title' => t('Swipe'),
    '#description' => t("Enables a swipe movement for flicking through images on touch devices."),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['swipe'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  // Carousel fieldset
  $form['views_jqfx_galleria']['behavior']['carousel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Carousel options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['views_jqfx_galleria']['behavior']['carousel']['carousel'] = array(
    '#type' => 'select',
    '#title' => t('Carousel'),
    '#description' => t('Galleria comes with a built-in horizontal carousel. This options is for activating / deactivating the carousel feature. Setting this to %true, the carousel will be automatically applied if the total som of thumbnails width exceeds the thumbnail container. This will be re-calculaed on resize.', array('%true' => t('true'))),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['carousel']['carousel'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['behavior']['carousel']['carousel_follow'] = array(
    '#type' => 'select',
    '#title' => t('Carousel follow'),
    '#description' => t('Has the carousel follow the active image.'),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['carousel']['carousel_follow'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-behavior-carousel-carousel' => array(TRUE)),
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $carousel_speed = drupal_map_assoc(array(50, 100, 150, 200, 300, 400, 500, 750, 1000));

  $form['views_jqfx_galleria']['behavior']['carousel']['carousel_speed'] = array(
    '#type' => 'select',
    '#title' => t('Carousel speed'),
    '#description' => t('The slide speed of the carousel in milliseconds.'),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['carousel']['carousel_speed'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-behavior-carousel-carousel' => array(TRUE)),
    '#options' => $carousel_speed,
  );

  $carousel_steps = drupal_map_assoc(array('auto', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

  $form['views_jqfx_galleria']['behavior']['carousel']['carousel_steps'] = array(
    '#type' => 'select',
    '#title' => t('Carousel steps'),
    '#description' => t('The number of "steps" the carousel will slide when navigating between available thumbnails. Specifying %auto will move the carousel as many steps as there are visible thumbnails.', array('%auto' => 'auto')),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['carousel']['carousel_steps'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-behavior-carousel-carousel' => array(TRUE)),
    '#options' => $carousel_steps,
  );

  // Idle mode fieldset
  $form['views_jqfx_galleria']['behavior']['idle_mode'] = array(
    '#type' => 'fieldset',
    '#title' => t('Idle mode options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['views_jqfx_galleria']['behavior']['idle_mode']['idle_mode'] = array(
    '#type' => 'select',
    '#title' => t('Idle mode'),
    '#description' => t('Global option for turning on/off idle mode. Eache gallery enters idle mode after certain amount of time and themes behave differently when this happens, f.ex clears the stage from distractions. If you want to prevent idle mode from ever occuring, set this to %false.', array('%false' => 'false')),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['idle_mode']['idle_mode'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $idle_speed = drupal_map_assoc(array(50, 100, 150, 200, 300, 400, 500, 750, 1000));

  $form['views_jqfx_galleria']['behavior']['idle_mode']['idle_speed'] = array(
    '#type' => 'select',
    '#title' => t('Idle speed'),
    '#description' => t("Controls the animation speed in milliseconds of the idle elements. An example is when the thumbnails and captions hide in the fullscreen theme after a period of inactivity."),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['idle_mode']['idle_speed'],
    '#dependency' => array('edit-style-options-views-jqfx-galleria-behavior-idle-mode-idle-mode' => array(TRUE)),
    '#options' => $idle_speed,
  );

  $idle_time = drupal_map_assoc(array(1000, 2000, 3000, 4000, 5000, 7500, 10000, 20000, 30000));

  $form['views_jqfx_galleria']['behavior']['idle_mode']['idle_time'] = array(
    '#type' => 'select',
    '#title' => t('Idle time'),
    '#description' => t("You can control the delay in milliseconds before Galleria falls into idle mode using this option."),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['idle_mode']['idle_time'],
    '#dependency' => array('edit-style-options-views-jqfx-galleria-behavior-idle-mode-idle-mode' => array(TRUE)),
    '#options' => $idle_time,
  );

  // Image pan fieldset
  $form['views_jqfx_galleria']['behavior']['image_pan'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image pan options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['views_jqfx_galleria']['behavior']['image_pan']['image_pan'] = array(
    '#type' => 'select',
    '#title' => t('Image pan'),
    '#description' => t('Galleria comes with a built-in panning effect. The effect is sometimes useful if you have cropped images and want to let the users pan across the stage to see the entire image. Enable image pan to apply a mouse-controlled movement of the image to reveal the cropped parts.'),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['image_pan']['image_pan'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['behavior']['image_pan']['image_pan_smoothness'] = array(
    '#type' => 'textfield',
    '#title' => t('Image pan smoothness'),
    '#description' => t('This value sets how "smooth" the image pan movement should be when setting image_pan is set to %true. The higher value, the smoother effect but also CPU consuming.', array('%true' => 'true')),
    '#default_value' => $view->options['views_jqfx_galleria']['behavior']['image_pan']['image_pan_smoothness'],
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-style-options-views-jqfx-galleria-behavior-image-pan-image-pan' => array(TRUE)),
  );

  // Transitions fieldset
  $form['views_jqfx_galleria']['transition'] = array(
    '#type' => 'fieldset',
    '#title' => t('Transition options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $transitions = array(
    '' => t('Not set'),
    'fade' => t('Fade'),
    'flash' => t('Flash'),
    'pulse' => t('Pulse'),
    'slide' => t('Slide'),
    'fadeslide' => t('Fade/Slide'),
  );

  $form['views_jqfx_galleria']['transition']['transition'] = array(
    '#type' => 'select',
    '#title' => t('Transition'),
    '#description' => t("The transition that is used when displaying the images. If a theme comes with a custom transition (like the lightbox theme) leave as not set and Galleria will use the theme default.<ul><li>%fade will fade between images.</li><li>%flash will fade into the background color between images.</li><li>%pulse quickly removes the image into background color, then fades the next image.</li><li>%slide will slide the images using the Galleria easing depending on image position.</li><li>%fadeslide will fade between images and slide slightly at the same time.</li></ul>", array('%fade' => t('Fade'), '%flash' => t('Flash'), '%pulse' => t('Pulse'), '%slide' => t('Slide'), '%fadeslide' => t('Fade/Slide')), array('langcode' => 'en')),
    '#default_value' => $view->options['views_jqfx_galleria']['transition']['transition'],
    '#options' => $transitions,
  );

  $form['views_jqfx_galleria']['transition']['transition_initial'] = array(
    '#type' => 'select',
    '#title' => t('Transition initial'),
    '#description' => t("Optionally set a different transition for the first image"),
    '#default_value' => $view->options['views_jqfx_galleria']['transition']['transition_initial'],
    '#options' => $transitions,
  );

  $transition_speed = drupal_map_assoc(array(50, 100, 150, 200, 300, 400, 500, 750, 1000, 1500, 2000));

  $form['views_jqfx_galleria']['transition']['transition_speed'] = array(
    '#type' => 'select',
    '#title' => t('Transition speed'),
    '#description' => t("The milliseconds used when applying the transition."),
    '#default_value' => $view->options['views_jqfx_galleria']['transition']['transition_speed'],
    '#options' => $transition_speed,
  );

  $form['views_jqfx_galleria']['transition']['easing'] = array(
    '#type' => 'textfield',
    '#title' => t('Easing'),
    '#description' => t('You can use this option to control the animation easing on a global level in Galleria. Besides the built-in jQuery easings %linear and %swing, Galleria includes the following easings:<ul><li>%galleria</li><li>%galleriaIn</li><li>%galleriaOut</li></ul>You can use any of these easings or any other easing plugin, f.ex the jQuery Easing Plugin.', array('%linear' => t('linear'), '%swing' => t('swing'), '%galleria' => t('galleria'), '%galleriaIn' => t('galleriaIn'), '%galleriaOut' => t('galleriaOut'))),
    '#default_value' => $view->options['views_jqfx_galleria']['transition']['easing'],
  );

  // Lightbox fieldset
  $form['views_jqfx_galleria']['lightbox'] = array(
    '#type' => 'fieldset',
    '#title' => t('Lightbox options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['views_jqfx_galleria']['lightbox']['lightbox'] = array(
    '#type' => 'select',
    '#title' => t('Lightbox'),
    '#description' => t('This option acts as a helper for attaching a lightbox when the user clicks on an image. If you have a link defined for the image, the link will take precedence.'),
    '#default_value' => $view->options['views_jqfx_galleria']['lightbox']['lightbox'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $lightbox_speed = drupal_map_assoc(array(50, 100, 150, 200, 300, 400, 500, 750, 1000, 1500, 2000));

  $form['views_jqfx_galleria']['lightbox']['lightbox_fade_speed'] = array(
    '#type' => 'select',
    '#title' => t('Lightbox fade speed'),
    '#description' => t("When calling ``.showLightbox()`` the lightbox will animate and fade the images and captions. This value controls how fast they should fade in milliseconds."),
    '#default_value' => $view->options['views_jqfx_galleria']['lightbox']['lightbox_fade_speed'],
    '#options' => $lightbox_speed,
  );

  $form['views_jqfx_galleria']['lightbox']['lightbox_transition_speed'] = array(
    '#type' => 'select',
    '#title' => t('Lightbox transition speed'),
    '#description' => t("When calling ``.showLightbox()`` the lightbox will animate the white square before displaying the image. This value controls how fast it should animate in milliseconds."),
    '#default_value' => $view->options['views_jqfx_galleria']['lightbox']['lightbox_transition_speed'],
    '#options' => $lightbox_speed,
  );

  $form['views_jqfx_galleria']['lightbox']['overlay_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Overlay background'),
    '#description' => t("This defines the overlay background color when calling ``showLightbox()``."),
    '#default_value' => $view->options['views_jqfx_galleria']['lightbox']['overlay_background'],
  );

  $form['views_jqfx_galleria']['lightbox']['overlay_opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Overlay opacity'),
    '#description' => t("This sets how much opacity the overlay should have when calling ``showLightbox()``."),
    '#default_value' => $view->options['views_jqfx_galleria']['lightbox']['overlay_opacity'],
  );

  // Advanced fieldset
  $form['views_jqfx_galleria']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced options'),
    '#description' => t('Caution: experts only!. See: !url for examples.', array('!url' => l(t('http://galleria.aino.se/docs/1.2/', array(), array('langcode' => 'en')), 'http://galleria.aino.se/docs/1.2/', array('attributes' => array('target' => '_blank')))), array('langcode' => 'en')),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['views_jqfx_galleria']['advanced']['debug'] = array(
    '#type' => 'select',
    '#title' => t('Debug'),
    '#description' => t('By default, Galleria fails most errors silently, but in development mode you should turn debug on to throw errors when something is not right.'),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['debug'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['advanced']['minify_js'] = array(
    '#type' => 'select',
    '#title' => t('Use minified javascript'),
    '#description' => t('When selected the minified version of the galleria plugin will be loaded to improve page speed. Be sure this file has been renamed to galleria.min.js with the release number removed.'),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['minify_js'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $current_theme = variable_get('theme_default','none');
  $js_region = system_region_list($current_theme, $show = REGIONS_ALL);

  $form['views_jqfx_galleria']['advanced']['js_region'] = array(
    '#type' => 'select',
    '#title' => t('Javascript region'),
    '#description' => t("Some galleria javascript functions need to be added at the bottom of the page. This option defaults to %footer. If your site theme doesn't have a %footer choose another region.", array('%footer' => 'footer')),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['js_region'],
    '#options' => $js_region,
  );

  $form['views_jqfx_galleria']['advanced']['history'] = array(
    '#type' => 'select',
    '#title' => t('History'),
    '#description' => t('This option loads the history plugin to create permalinks for images. When enabled a url will be created for each image within the gallery, and using the browser back button will navigate to the previous image rather than the previous page.'),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['history'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['advanced']['keep_source'] = array(
    '#type' => 'select',
    '#title' => t('Keep source'),
    '#description' => t('By default, Galleria clears the source container when rendering the gallery. Sometimes you need to apply the gallery some place else, like a lightbox, but still want to keep the thumbnails in the source. This option sets if the source HTML should be left intact. Setting this to ``true`` will also add click events inside the source code, to make your thumbnails clickable. Useful for building custom thumbnails and still have galleria control the gallery.'),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['keep_source'],
    '#options' => array(
      FALSE => t('Disabled'),
      TRUE => t('Enabled'),
    ),
  );

  $form['views_jqfx_galleria']['advanced']['data_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Data selector'),
    '#description' => t("The selector Galleria should look for in the HTML source. If left empty Galleria will default to 'img'. If you are using other elements than images to store data in the HTML, you can set this option to configure Galleria to look for the right elements. You can use any jQuery selector."),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['data_selector'],
  );

  $form['views_jqfx_galleria']['advanced']['data_source'] = array(
    '#type' => 'textfield',
    '#title' => t('Data source'),
    '#description' => t("This is for defining where to look for the Galleria data. By default, Galleria looks for HTML data in the target selector (in this module it's typically '#views-jqfx-galleria-images-1'), but you can tell Galleria to look elsewhere in the document using this option. If you are using JSON data, you can use this option to bring that JSON Array into Galleria."),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['data_source'],
  );

  $form['views_jqfx_galleria']['advanced']['data_config'] = array(
    '#type' => 'textarea',
    '#title' => t('Data config'),
    '#description' => t("If html layers are enabled a dataConfig function will be passed. However, any function you place in here will override it. This very useful function configures how the data should be extracted from the source. It should return an object that will blend in with the default extractions. Use this option to control how your data should be interpreted. A common case is when you have HTML markup that you would like to implement as captions. This option can tell Galleria how to interpret your HTML code so it collects the right data. The argument is a HTML element selected from the HTML source (most often an Image element). Use this to traverse the source and return the right data into Galleria. If you are using other elements than Images as source, you can change the selector using the data selector option."),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['data_config'],
    '#rows' => 10,
  );

  $form['views_jqfx_galleria']['advanced']['extend'] = array(
    '#type' => 'textarea',
    '#title' => t('Extend'),
    '#description' => t("This function is used to extend the init function of the theme. You will have full access to the Galleria API here. The argument is the cascaded options object, and the scope is always the Galleria gallery instance. Use extend as a method for adding custom modifications such as play/pause without creating a new theme."),
    '#default_value' => $view->options['views_jqfx_galleria']['advanced']['extend'],
    '#rows' => 10,
  );
}

/**
 * Implements hook_views_jqfx_options_form_validate().
 */
function views_jqfx_galleria_views_jqfx_options_form_validate(&$form, &$form_state, &$view) {
  if (!is_numeric($form_state['values']['style_options']['views_jqfx_galleria']['image']['image_margin'])) {
    form_error($form['views_jqfx_galleria']['image']['image_margin'], t('!setting must be numeric!', array('Image margin')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_jqfx_galleria']['image']['min_scale_ratio'])) {
    form_error($form['views_jqfx_galleria']['image']['min_scale_ratio'], t('!setting must be numeric!', array('Min scale ratio')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_jqfx_galleria']['image']['max_scale_ratio'])) {
    form_error($form['views_jqfx_galleria']['image']['max_scale_ratio'], t('!setting must be numeric!', array('Max scale ratio')));
  }
  if (!is_numeric($form_state['values']['style_options']['behavior']['image_pan']['views_jqfx_galleria']['image_pan_smoothness'])) {
    form_error($form['views_jqfx_galleria']['behavior']['image_pan']['image_pan_smoothness'], t('!setting must be numeric!', array('Image pan smoothness')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_jqfx_galleria']['image']['thumbnails']['thumb_margin'])) {
    form_error($form['views_jqfx_galleria']['image']['thumbnails']['thumb_margin'], t('!setting must be numeric!', array('Thumb margin')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_jqfx_galleria']['views_jqfx_galleria']['lightbox']['overlay_background'])) {
    form_error($form['views_jqfx_galleria']['lightbox']['overlay_background'], t('!setting must be numeric!', array('Thumb margin')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_jqfx_galleria']['views_jqfx_galleria']['lightbox']['overlay_opacity'])) {
    form_error($form['views_jqfx_galleria']['lightbox']['overlay_opacity'], t('!setting must be numeric!', array('Thumb margin')));
  }
}
