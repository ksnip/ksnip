
GIT_COMMIT="$GITHUB_SHA"
GIT_REPO_SLUG="$GITHUB_REPOSITORY"
if [[ "$GITHUB_REF" == "refs/tags/"* ]] ; then
  GIT_TAG="${GITHUB_REF#refs/tags/}"
fi

release_url="https://api.github.com/repos/$GIT_REPO_SLUG/releases/tags/$RELEASE_NAME"
echo "Getting the release ID..."
echo "release_url: $release_url"
release_infos=$(curl -XGET --header "Authorization: token ${GITHUB_TOKEN}" "${release_url}")
echo "release_infos: $release_infos"
release_id=$(echo "$release_infos" | grep "\"id\":" | head -n 1 | tr -s " " | cut -f 3 -d" " | cut -f 1 -d ",")
echo "release ID: $release_id"
upload_url=$(echo "$release_infos" | grep '"upload_url":' | head -n 1 | cut -d '"' -f 4 | cut -d '{' -f 1)
echo "upload_url: $upload_url"
release_url=$(echo "$release_infos" | grep '"url":' | head -n 1 | cut -d '"' -f 4 | cut -d '{' -f 1)
echo "release_url: $release_url"
target_commit_sha=$(echo "$release_infos" | grep '"target_commitish":' | head -n 1 | cut -d '"' -f 4 | cut -d '{' -f 1)
echo "target_commit_sha: $target_commit_sha"

if [ "$GIT_COMMIT" != "$target_commit_sha" ] ; then

  echo "GIT_COMMIT != target_commit_sha, hence deleting $RELEASE_NAME..."

  if [ ! -z "$release_id" ]; then
    delete_url="https://api.github.com/repos/$GIT_REPO_SLUG/releases/$release_id"
    echo "Delete the release..."
    echo "delete_url: $delete_url"
#    curl -XDELETE \
#        --header "Authorization: token ${GITHUB_TOKEN}" \
#        "${delete_url}"
  fi

#  # echo "Checking if release with the same name is still there..."
#  # echo "release_url: $release_url"
#  # curl -XGET --header "Authorization: token ${GITHUB_TOKEN}" \
#  #     "$release_url"
#
#  if [ "$RELEASE_NAME" == "continuous" ] ; then
#    # if this is a continuous build tag, then delete the old tag
#    # in preparation for the new release
#    echo "Delete the tag..."
#    delete_url="https://api.github.com/repos/$GIT_REPO_SLUG/git/refs/tags/$RELEASE_NAME"
#    echo "delete_url: $delete_url"
#    curl -XDELETE \
#        --header "Authorization: token ${GITHUB_TOKEN}" \
#        "${delete_url}"
#  fi
#
#  echo "Create release..."
#
#  release_infos=$(curl -H "Authorization: token ${GITHUB_TOKEN}" \
#       --data '{"tag_name": "'"$RELEASE_NAME"'","target_commitish": "'"$GIT_COMMIT"'","name": "'"$RELEASE_TITLE"'","body": "'"$RELEASE_BODY"'","draft": false,"prerelease": '$is_prerelease'}' "https://api.github.com/repos/$GIT_REPO_SLUG/releases")
#
#  echo "$release_infos"
#
#  unset upload_url
#  upload_url=$(echo "$release_infos" | grep '"upload_url":' | head -n 1 | cut -d '"' -f 4 | cut -d '{' -f 1)
#  echo "upload_url: $upload_url"
#
#  unset release_url
#  release_url=$(echo "$release_infos" | grep '"url":' | head -n 1 | cut -d '"' -f 4 | cut -d '{' -f 1)
#  echo "release_url: $release_url"

fi # if [ "$GIT_COMMIT" != "$tag_sha" ]