// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.omnibox.suggestions;

import org.chromium.build.annotations.NullMarked;
import org.chromium.components.omnibox.AutocompleteMatch;
import org.chromium.url.GURL;

/** A mechanism for creating {@link SuggestionViewDelegate}s. */
@NullMarked
public interface SuggestionHost {
    /**
     * Triggered when the user selects to refine one of the omnibox suggestions.
     *
     * @param suggestion Suggestion to use to refine Omnibox query.
     */
    void onRefineSuggestion(AutocompleteMatch suggestion);

    /**
     * Triggered when the user selects one of the omnibox suggestions to navigate to.
     *
     * @param suggestion User-selected Suggestion.
     * @param position The position of the suggestion on the list.
     * @param url The specific URL associated with the suggestion to navigate to.
     */
    void onSuggestionClicked(AutocompleteMatch suggestion, int position, GURL url);

    /**
     * Triggered when the user long presses the omnibox suggestion.
     *
     * @param suggestion Long-pressed Suggestion.
     * @param position The position of the suggestion on the list.
     */
<<<<<<< HEAD
    void onSuggestionTouchDown(AutocompleteMatch suggestion, int position);

    /**
     * Triggered when the user clicks one of the OmniboxActions attached to Suggestion.
     *
     * @param action the action the user interacted with
     * @param position The position of the associated suggestion.
     */
    void onOmniboxActionClicked(OmniboxAction action, int position);

    /**
     * Triggered when the user long presses the omnibox suggestion. Deletes the entire
     * AutocompleteMatch. Execution of this method implies removal of the AutocompleteMatch.
     *
     * @param suggestion Long-pressed Suggestion.
     * @param titleText The title to display in the delete dialog.
     */
    void onDeleteMatch(AutocompleteMatch suggestion, String titleText);

    /**
     * Triggered when the user long presses the omnibox suggestion element (eg. tile). Performs
     * partial deletion of an AutocompleteMatch, focusing on the supplied element. Execution of this
     * method does not imply removal of the AutocompleteMatch.
     *
     * @param suggestion Long-pressed Suggestion.
     * @param titleText The title to display in the delete dialog.
     * @param element Element of the suggestion to be deleted.
     */
    void onDeleteMatchElement(AutocompleteMatch suggestion, String titleText, int element);
=======
    void onSuggestionLongClicked(@NonNull AutocompleteMatch suggestion, int position);
>>>>>>> chromium

    /**
     * Triggered when the user selects a switch to tab action.
     *
     * @param suggestion Suggestion for which a corresponding tab is already open.
     * @param position The position of the suggestion on the list.
     */
    void onSwitchToTab(AutocompleteMatch suggestion, int position);

    /**
     * Toggle expanded state of suggestion items belonging to specific group.
     *
     * @param groupId ID of Suggestion Group whose visibility changed.
     * @param isCollapsed True if group should appear collapsed, otherwise false.
     */
    void setGroupCollapsedState(int groupId, boolean isCollapsed);

    /**
     * Update the content of the Omnibox without triggering the Navigation.
     *
     * @param text The text to be displayed in the Omnibox.
     */
<<<<<<< HEAD
    void setOmniboxEditingText(String text);

    /** Clear focus, close the suggestions list and complete the interaction with the Omnibox. */
    void finishInteraction();
=======
    void setOmniboxEditingText(@NonNull String text);
>>>>>>> chromium
}
