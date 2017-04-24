<?php

/**
 * @file
 * Theme settings for the theme875
 */
function theme875_form_system_theme_settings_alter(&$form, &$form_state) {
	/**
	 * Breadcrumb settings
	 */
	$form['theme875_breadcrumb'] = array(
		'#type' => 'fieldset',
		'#title' => t('Breadcrumb'),
	);
	
	$form['theme875_breadcrumb']['theme875_breadcrumb_display'] = array(
		'#type' => 'select',
		'#title' => t('Display breadcrumb'),
		'#default_value' => theme_get_setting('theme875_breadcrumb_display'),
		'#options' => array(
			'yes' => t('Yes'),
			'no' => t('No'),
		),
	);
	
	$form['theme875_breadcrumb']['theme875_breadcrumb_hideonlyfront'] = array(
		'#type' => 'checkbox',
		'#title' => t('Hide the breadcrumb if the breadcrumb only contains the link to the front page.'),
		'#default_value' => theme_get_setting('theme875_breadcrumb_hideonlyfront'),
	);
	
	$form['theme875_breadcrumb']['theme875_breadcrumb_showtitle'] = array(
		'#type' => 'checkbox',
		'#title' => t('Show page title on breadcrumb.'),
		'#default_value' => theme_get_setting('theme875_breadcrumb_showtitle'),
	);

	$form['theme875_breadcrumb']['theme875_breadcrumb_separator'] = array(
		'#type' => 'textfield',
		'#title' => t('Breadcrumb separator'),
		'#default_value' => theme_get_setting('theme875_breadcrumb_separator'),
	);
}