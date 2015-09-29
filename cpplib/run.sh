make remove && make
snip_path=$PWD/cpp_code/tree_and_SNIP/Euro
#snip_path=$PWD/cpp_code/tree_and_SNIP/Euro
#snip_path=$PWD/cpp_code/tree_and_SNIP/sub
selected_snip_path="${snip_path}_SNIP"
#classifier_type="continent"
classifier_type="country"
#./ethnopred_once -i cpp_code/csv/test5.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
time ./ethnopred_once -i cpp_code/csv/test_forward_European.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred -i cpp_code/csv/test.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
