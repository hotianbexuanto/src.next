// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.omnibox.suggestions;

import org.chromium.ui.modelutil.MVCListAdapter.ModelList;
import org.chromium.ui.modelutil.PropertyKey;
<<<<<<< HEAD
import org.chromium.ui.modelutil.PropertyModel.ReadableBooleanPropertyKey;
import org.chromium.ui.modelutil.PropertyModel.ReadableObjectPropertyKey;
=======
>>>>>>> chromium
import org.chromium.ui.modelutil.PropertyModel.WritableBooleanPropertyKey;
import org.chromium.ui.modelutil.PropertyModel.WritableObjectPropertyKey;

/**
 * The properties controlling the state of the list of suggestion items.
 */
public class SuggestionListProperties {
    /** Whether the suggestion list is visible. */
    public static final WritableBooleanPropertyKey VISIBLE = new WritableBooleanPropertyKey();

    /** The embedder for the suggestion list. */
<<<<<<< HEAD
    static final ReadableObjectPropertyKey<OmniboxSuggestionsDropdownEmbedder> EMBEDDER =
            new ReadableObjectPropertyKey<>();

    /** The list of models controlling the state of the suggestion items. */
    static final ReadableObjectPropertyKey<ModelList> SUGGESTION_MODELS =
            new ReadableObjectPropertyKey<>();
=======
    public static final WritableObjectPropertyKey<OmniboxSuggestionsDropdownEmbedder> EMBEDDER =
            new WritableObjectPropertyKey<>();

    /**
     * The list of models controlling the state of the suggestion items. This should never be
     * bound to the same view more than once.
     */
    public static final WritableObjectPropertyKey<ModelList> SUGGESTION_MODELS =
            new WritableObjectPropertyKey<>(true);
>>>>>>> chromium

    /** Whether the suggestion list should have a dark background. */
    public static final WritableBooleanPropertyKey IS_INCOGNITO = new WritableBooleanPropertyKey();

    /** Observer that will receive notifications and callbacks from Suggestion List. */
    public static final WritableObjectPropertyKey<OmniboxSuggestionsDropdown.Observer> OBSERVER =
            new WritableObjectPropertyKey<>();

    public static final PropertyKey[] ALL_KEYS =
            new PropertyKey[] {VISIBLE, EMBEDDER, SUGGESTION_MODELS, IS_INCOGNITO, OBSERVER};
}
