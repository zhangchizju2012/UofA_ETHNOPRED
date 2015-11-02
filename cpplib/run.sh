#make remove && make
snip_path=$PWD/cpp_code/tree_and_SNIP/Sub
#snip_path=$PWD/cpp_code/tree_and_SNIP/Sub_East_Asian
#snip_path=$PWD/cpp_code/tree_and_SNIP/Sub_American
#snip_path=$PWD/cpp_code/tree_and_SNIP/Sub_Euro
#snip_path=$PWD/cpp_code/tree_and_SNIP/Sub_African
#snip_path=$PWD/cpp_code/tree_and_SNIP/Sub_Kenyan
#selected_snip_path=$PWD/cpp_code/tree_and_SNIP/sub_EuEaAf
selected_snip_path="${snip_path}_SNIP"
classifier_type="subcontinent"
#classifier_type="continent"
#classifier_type="country"
#time ./ethnopred_once -i cpp_code/csv/Kenyan_not_used.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/continent.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/test_forward_European.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
time ./ethnopred_once -i cpp_code/csv/All.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/African_used.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/All.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/northamerican_mix.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/149SNP.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/606.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/CGEMS_data.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
#time ./ethnopred_once -i cpp_code/csv/AFFY.csv -t ${snip_path} -s ${selected_snip_path} -T ${classifier_type}
