// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.omnibox.suggestions;

import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_ANSWER_TEXT_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_DESCRIPTION_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_DISPLAY_TEXT_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_GROUP_ID_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_HEADER_GROUP_COLLAPSED_BY_DEFAULT_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_HEADER_GROUP_ID_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_HEADER_GROUP_TITLE_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_IS_DELETABLE_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_IS_SEARCH_TYPE_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_NATIVE_SUBTYPES_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_NATIVE_TYPE_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_POST_CONTENT_DATA_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_POST_CONTENT_TYPE_PREFIX;
import static org.chromium.chrome.browser.preferences.ChromePreferenceKeys.KEY_ZERO_SUGGEST_URL_PREFIX;

import android.text.TextUtils;
import android.util.Base64;
import android.util.SparseArray;

<<<<<<< HEAD
=======
import androidx.annotation.NonNull;
>>>>>>> chromium
import androidx.annotation.VisibleForTesting;
import androidx.collection.ArraySet;

<<<<<<< HEAD
import com.google.protobuf.InvalidProtocolBufferException;

import org.chromium.base.ContextUtils;
import org.chromium.build.annotations.NullMarked;
import org.chromium.build.annotations.Nullable;
=======
import org.chromium.base.Function;
import org.chromium.chrome.browser.omnibox.MatchClassificationStyle;
import org.chromium.chrome.browser.omnibox.OmniboxSuggestionType;
>>>>>>> chromium
import org.chromium.chrome.browser.preferences.ChromePreferenceKeys;
import org.chromium.chrome.browser.preferences.SharedPreferencesManager;
import org.chromium.components.omnibox.AutocompleteMatch;
import org.chromium.components.omnibox.AutocompleteResult;
import org.chromium.components.omnibox.AutocompleteResult.GroupDetails;
import org.chromium.url.GURL;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;

<<<<<<< HEAD
/** CachedZeroSuggestionsManager manages caching and restoring zero suggestions. */
@NullMarked
public class CachedZeroSuggestionsManager {
    /** Jump-Start Omnibox: the context of the most recently visited page. */
    public static class JumpStartContext {
        /** The GURL representing the most recently visited page. */
        public final GURL url;

        /** {@link PageClassification} value associated with the most recently visited page. */
        public final int pageClass;

        public JumpStartContext(GURL url, int pageClass) {
            this.url = url;
            this.pageClass = pageClass;
        }
    }

    /** Persisted Search Engine metadata. */
    public static class SearchEngineMetadata {
        /** The keyword associated with the search engine. */
        public final String keyword;

        public SearchEngineMetadata(String keyword) {
            this.keyword = keyword;
        }
    }

    @VisibleForTesting
    /* package */ static final String KEY_JUMP_START_URL = "omnibox:jump_start:url";

    @VisibleForTesting
    /* package */ static final String KEY_JUMP_START_PAGE_CLASS = "omnibox:jump_start:page_class";

    @VisibleForTesting /* package */ static final String KEY_DSE_KEYWORD = "omnibox:dse:keyword";

    @VisibleForTesting
    /* package */ static final Set<String> ADDITIONAL_KEYS_TO_ERASE =
            Set.of(KEY_JUMP_START_URL, KEY_JUMP_START_PAGE_CLASS);

    /** Save the content of the CachedZeroSuggestionsManager to SharedPreferences cache. */
    @SuppressWarnings("ApplySharedPref")
    public static void saveToCache(int pageClass, AutocompleteResult resultToCache) {
        SharedPreferences prefs = ContextUtils.getAppSharedPreferences();

        var serializedBytes = resultToCache.serialize().toByteArray();

        // Note: this code has very little time to run. Be sure data is persisted. Don't use
        // asynchronous `apply()` method, because the asynchronously persisted details may never
        // make it to the data file.
        prefs.edit()
                .putString(
                        getCacheKey(pageClass),
                        Base64.encodeToString(serializedBytes, Base64.DEFAULT))
                .commit();

        eraseOldCachedData();
    }

    /** Save the details related to currently selected Search Engine. */
    public static void saveSearchEngineMetadata(SearchEngineMetadata metadata) {
        SharedPreferences.Editor editor = ContextUtils.getAppSharedPreferences().edit();
        editor.putString(KEY_DSE_KEYWORD, metadata.keyword).apply();
    }

    /** Returns the details of the currently persisted Search Engine. */
    public static @Nullable SearchEngineMetadata readSearchEngineMetadata() {
        SharedPreferences prefs = ContextUtils.getAppSharedPreferences();
        var keyword = prefs.getString(KEY_DSE_KEYWORD, null);
        if (TextUtils.isEmpty(keyword)) return null;

        return new SearchEngineMetadata(keyword);
=======
/**
 * CachedZeroSuggestionsManager manages caching and restoring zero suggestions.
 */
public class CachedZeroSuggestionsManager {
    /**
     * Save the content of the CachedZeroSuggestionsManager to SharedPreferences cache.
     */
    public static void saveToCache(AutocompleteResult resultToCache) {
        final SharedPreferencesManager manager = SharedPreferencesManager.getInstance();
        cacheSuggestionList(manager, resultToCache.getSuggestionsList());
        cacheGroupsDetails(manager, resultToCache.getGroupsDetails());
>>>>>>> chromium
    }

    /**
     * Read previously stored AutocompleteResult from cache.
     * @return AutocompleteResult populated with the content of the SharedPreferences cache.
     */
<<<<<<< HEAD
    static AutocompleteResult readFromCache(int pageClass) {
        SharedPreferences prefs = ContextUtils.getAppSharedPreferences();
        String key = getCacheKey(pageClass);
=======
    static AutocompleteResult readFromCache() {
        final SharedPreferencesManager manager = SharedPreferencesManager.getInstance();
        List<AutocompleteMatch> suggestions =
                CachedZeroSuggestionsManager.readCachedSuggestionList(manager);
        SparseArray<GroupDetails> groupsDetails =
                CachedZeroSuggestionsManager.readCachedGroupsDetails(manager);
        removeInvalidSuggestionsAndGroupsDetails(suggestions, groupsDetails);
        return AutocompleteResult.fromCache(suggestions, groupsDetails);
    }
>>>>>>> chromium

    /**
     * Cache suggestion list in shared preferences.
     *
     * @param prefs Shared preferences manager.
     */
    private static void cacheSuggestionList(
            SharedPreferencesManager prefs, List<AutocompleteMatch> suggestions) {
        int numCachableSuggestions = 0;

        // Write 0 here to avoid something wrong in the for loop, and the real size will be updated
        // after the for loop.
        prefs.writeInt(ChromePreferenceKeys.KEY_ZERO_SUGGEST_LIST_SIZE, 0);
        for (int i = 0; i < suggestions.size(); i++) {
            AutocompleteMatch suggestion = suggestions.get(i);
            if (!shouldCacheSuggestion(suggestion)) continue;

            prefs.writeString(KEY_ZERO_SUGGEST_URL_PREFIX.createKey(numCachableSuggestions),
                    suggestion.getUrl().serialize());
            prefs.writeString(
                    KEY_ZERO_SUGGEST_DISPLAY_TEXT_PREFIX.createKey(numCachableSuggestions),
                    suggestion.getDisplayText());
            prefs.writeString(KEY_ZERO_SUGGEST_DESCRIPTION_PREFIX.createKey(numCachableSuggestions),
                    suggestion.getDescription());
            prefs.writeInt(KEY_ZERO_SUGGEST_NATIVE_TYPE_PREFIX.createKey(numCachableSuggestions),
                    suggestion.getType());
            prefs.writeStringSet(
                    KEY_ZERO_SUGGEST_NATIVE_SUBTYPES_PREFIX.createKey(numCachableSuggestions),
                    convertSet(suggestion.getSubtypes(), v -> v.toString()));
            prefs.writeBoolean(
                    KEY_ZERO_SUGGEST_IS_SEARCH_TYPE_PREFIX.createKey(numCachableSuggestions),
                    suggestion.isSearchSuggestion());
            prefs.writeBoolean(
                    KEY_ZERO_SUGGEST_IS_DELETABLE_PREFIX.createKey(numCachableSuggestions),
                    suggestion.isDeletable());
            prefs.writeString(
                    KEY_ZERO_SUGGEST_POST_CONTENT_TYPE_PREFIX.createKey(numCachableSuggestions),
                    suggestion.getPostContentType());
            prefs.writeString(
                    KEY_ZERO_SUGGEST_POST_CONTENT_DATA_PREFIX.createKey(numCachableSuggestions),
                    suggestion.getPostData() == null
                            ? null
                            : Base64.encodeToString(suggestion.getPostData(), Base64.DEFAULT));
            prefs.writeInt(KEY_ZERO_SUGGEST_GROUP_ID_PREFIX.createKey(numCachableSuggestions),
                    suggestion.getGroupId());
            numCachableSuggestions++;
        }
        prefs.writeInt(ChromePreferenceKeys.KEY_ZERO_SUGGEST_LIST_SIZE, numCachableSuggestions);
    }

    /**
     * Restore suggestion list from shared preferences.
     *
     * @param prefs Shared preferences manager.
     * @return List of Omnibox suggestions previously cached in shared preferences.
     */
    @NonNull
    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    static List<AutocompleteMatch> readCachedSuggestionList(SharedPreferencesManager prefs) {
        int size = prefs.readInt(ChromePreferenceKeys.KEY_ZERO_SUGGEST_LIST_SIZE, -1);
        if (size <= 1) {
            // Ignore case where we only have a single item on the list - it's likely
            // 'what-you-typed' suggestion.
            size = 0;
        }

        List<AutocompleteMatch> suggestions = new ArrayList<>(size);
        List<AutocompleteMatch.MatchClassification> classifications = new ArrayList<>();
        classifications.add(
                new AutocompleteMatch.MatchClassification(0, MatchClassificationStyle.NONE));
        for (int i = 0; i < size; i++) {
            // TODO(tedchoc): Answers in suggest were previously cached, but that could lead to
            //                stale or misleading answers for cases like weather.  Ignore any
            //                previously cached answers for several releases while any previous
            //                results are cycled through.
            String answerText =
                    prefs.readString(KEY_ZERO_SUGGEST_ANSWER_TEXT_PREFIX.createKey(i), null);
            if (!TextUtils.isEmpty(answerText)) continue;

            GURL url = GURL.deserialize(
                    prefs.readString(KEY_ZERO_SUGGEST_URL_PREFIX.createKey(i), null));
            String displayText =
                    prefs.readString(KEY_ZERO_SUGGEST_DISPLAY_TEXT_PREFIX.createKey(i), null);
            String description =
                    prefs.readString(KEY_ZERO_SUGGEST_DESCRIPTION_PREFIX.createKey(i), null);
            int nativeType = prefs.readInt(KEY_ZERO_SUGGEST_NATIVE_TYPE_PREFIX.createKey(i),
                    AutocompleteMatch.INVALID_TYPE);
            boolean isSearchType =
                    prefs.readBoolean(KEY_ZERO_SUGGEST_IS_SEARCH_TYPE_PREFIX.createKey(i), false);
            boolean isDeletable =
                    prefs.readBoolean(KEY_ZERO_SUGGEST_IS_DELETABLE_PREFIX.createKey(i), false);
            String postContentType =
                    prefs.readString(KEY_ZERO_SUGGEST_POST_CONTENT_TYPE_PREFIX.createKey(i), null);
            String postDataStr =
                    prefs.readString(KEY_ZERO_SUGGEST_POST_CONTENT_DATA_PREFIX.createKey(i), null);
            byte[] postData =
                    postDataStr == null ? null : Base64.decode(postDataStr, Base64.DEFAULT);
            int groupId = prefs.readInt(
                    KEY_ZERO_SUGGEST_GROUP_ID_PREFIX.createKey(i), AutocompleteMatch.INVALID_GROUP);

            Set<Integer> subtypes = null;
            try {
                Set<String> subtypeStrings = prefs.readStringSet(
                        KEY_ZERO_SUGGEST_NATIVE_SUBTYPES_PREFIX.createKey(i), null);
                subtypes = convertSet(subtypeStrings, v -> Integer.parseInt(v));
            } catch (NumberFormatException e) {
                // Subtype information contains malformed elements, suggesting that the
                // entire cache may be damaged.
                return Collections.emptyList();
            }

            AutocompleteMatch suggestion = new AutocompleteMatch(nativeType, subtypes, isSearchType,
                    0, 0, displayText, classifications, description, classifications, null, null,
                    url, GURL.emptyGURL(), null, isDeletable, postContentType, postData, groupId,
                    null, null, false, null);
            suggestions.add(suggestion);
        }

        return suggestions;
    }

    /**
     * Cache suggestion group details in shared preferences.
     *
     * @param prefs Shared preferences manager.
     * @param groupsDetails Map of Group ID to GroupDetails.
     */
    private static void cacheGroupsDetails(
            SharedPreferencesManager prefs, SparseArray<GroupDetails> groupsDetails) {
        final int size = groupsDetails.size();
        prefs.writeInt(ChromePreferenceKeys.KEY_ZERO_SUGGEST_HEADER_LIST_SIZE, size);
        for (int i = 0; i < size; i++) {
            final GroupDetails details = groupsDetails.valueAt(i);
            String title = details.title;
            boolean collapsedByDefault = details.collapsedByDefault;

            prefs.writeInt(
                    KEY_ZERO_SUGGEST_HEADER_GROUP_ID_PREFIX.createKey(i), groupsDetails.keyAt(i));
            prefs.writeString(KEY_ZERO_SUGGEST_HEADER_GROUP_TITLE_PREFIX.createKey(i), title);
            prefs.writeBoolean(
                    KEY_ZERO_SUGGEST_HEADER_GROUP_COLLAPSED_BY_DEFAULT_PREFIX.createKey(i),
                    collapsedByDefault);
        }
    }

    /**
     * Restore group details from shared preferences.
     *
     * @param prefs Shared preferences manager.
     * @return Map of group ID to GroupDetails previously cached in shared preferences.
     */
<<<<<<< HEAD
    public static JumpStartContext readJumpStartContext() {
        SharedPreferences prefs = ContextUtils.getAppSharedPreferences();
        String url = prefs.getString(KEY_JUMP_START_URL, UrlConstants.NTP_URL);
        int pageClass =
                prefs.getInt(
                        KEY_JUMP_START_PAGE_CLASS,
                        PageClassification.INSTANT_NTP_WITH_OMNIBOX_AS_STARTING_FOCUS_VALUE);
        return new JumpStartContext(new GURL(url), pageClass);
=======
    @NonNull
    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    static SparseArray<GroupDetails> readCachedGroupsDetails(SharedPreferencesManager prefs) {
        final int size = prefs.readInt(ChromePreferenceKeys.KEY_ZERO_SUGGEST_HEADER_LIST_SIZE, 0);
        final SparseArray<GroupDetails> groupsDetails = new SparseArray<>(size);

        for (int i = 0; i < size; i++) {
            int groupId = prefs.readInt(KEY_ZERO_SUGGEST_HEADER_GROUP_ID_PREFIX.createKey(i),
                    AutocompleteMatch.INVALID_GROUP);
            String groupTitle =
                    prefs.readString(KEY_ZERO_SUGGEST_HEADER_GROUP_TITLE_PREFIX.createKey(i), null);
            boolean collapsedByDefault = prefs.readBoolean(
                    KEY_ZERO_SUGGEST_HEADER_GROUP_COLLAPSED_BY_DEFAULT_PREFIX.createKey(i), false);

            groupsDetails.put(groupId, new GroupDetails(groupTitle, collapsedByDefault));
        }
        return groupsDetails;
>>>>>>> chromium
    }

    /**
     * Remove all invalid entries for group details map and omnibox suggestions list.
     *
     * @param suggestions List of suggestions to scan for invalid entries.
     * @param groupsDetails Map of GroupDetails to scan for invalid entries.
     */
    @VisibleForTesting(otherwise = VisibleForTesting.PRIVATE)
    static void removeInvalidSuggestionsAndGroupsDetails(
            List<AutocompleteMatch> suggestions, SparseArray<GroupDetails> groupsDetails) {
        // Remove all group details that have invalid index or title.
        for (int index = groupsDetails.size() - 1; index >= 0; index--) {
            if (groupsDetails.keyAt(index) == AutocompleteMatch.INVALID_GROUP
                    || TextUtils.isEmpty(groupsDetails.valueAt(index).title)) {
                groupsDetails.removeAt(index);
            }
        }

        // Remove all suggestions with no valid URL or pointing to nonexistent groups.
        for (int index = suggestions.size() - 1; index >= 0; index--) {
            final AutocompleteMatch suggestion = suggestions.get(index);
            final int groupId = suggestion.getGroupId();
            if (!suggestion.getUrl().isValid() || suggestion.getUrl().isEmpty()
                    || (groupId != AutocompleteMatch.INVALID_GROUP
                            && groupsDetails.indexOfKey(groupId) < 0)) {
                suggestions.remove(index);
            }
        }
    }

    /**
     * Check if the suggestion is needed to be cached.
     *
     * @param suggestion The AutocompleteMatch to check.
     * @return Whether or not the suggestion can be cached.
     */
    private static boolean shouldCacheSuggestion(AutocompleteMatch suggestion) {
        return !suggestion.hasAnswer()
                && suggestion.getType() != OmniboxSuggestionType.CLIPBOARD_URL
                && suggestion.getType() != OmniboxSuggestionType.CLIPBOARD_TEXT
                && suggestion.getType() != OmniboxSuggestionType.CLIPBOARD_IMAGE
                && suggestion.getType() != OmniboxSuggestionType.TILE_NAVSUGGEST;
    }

    /**
     * Convert the set of type T to set of type U objects.
     *
     * @param <T> Type of data held in the input set (inferred).
     * @param <U> Type of data held in the output set (inferred).
     * @param input Input set.
     * @param converter Function object that converts type T into type U.
     * @return A set of input objects converted to string.
     */
    private static <T, U> Set<U> convertSet(Set<T> input, Function<T, U> converter) {
        if (input == null) return null;

        Set<U> result = new ArraySet<>(input.size());
        for (T item : input) {
            result.add(converter.apply(item));
        }
        return result;
    }
}
