import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * @author Haomin Yu
 * @Description: Reads data from a CSV file, with header, and outputs C code to a file that
 *               can directly copy-pasted into an C array initialization
 *               (Class wrote generically; May work for other file types)
 *               For reuse, ensure that 'CSV_FILE', 'OUTPUT_FILE', and 'CSV_SPLIT_BY' is correct
 */

public class Initialization_Generator {
    public static final String CSV_FILE = "test_fsw_inputs.csv";
    public static final String CSV_SPLIT_BY = ",";
    public static final String OUTPUT_FILE = "Generated_C_Output.txt";
    
    public static void main(String[] args) throws IOException {
        List<List<String>> storage = new ArrayList<>();
        String line = "";
        // Reading the CSV file
        BufferedReader reader = new BufferedReader(new FileReader(CSV_FILE));
        while ((line = reader.readLine()) != null) {
            String[] toStore = line.split(CSV_SPLIT_BY);
            storage.add(Arrays.asList(toStore));
        }
        // Outputting results and formatted C code
        System.out.println("Total Entries: " + storage.size() + " (Including header)");
        System.out.println("========================================================");
        Map<String, Integer> header = getHeaderCount(storage.get(0));
        PrintWriter writer = new PrintWriter(OUTPUT_FILE, "UTF-8");
        for(int i = 1; i < storage.size() - 1; i++) {
            writer.println(formatLineToC(storage.get(i), header) + ",");
        }
        writer.println(formatLineToC(storage.get(storage.size() - 1), header));
        // Handling resource leak
        reader.close();
        writer.close();
    }
    
    /**
     * @param line       : A List of the data from the CSV file (One row of data)
     * @param headerCount: A Map that maps each header name to its occurrences
     *                     (Result from getHeaderCount(List<String>))
     * @return           : Formatted C code for array initialization
     */
    public static String formatLineToC(List<String> line, Map<String, Integer> headerCount) {
        Map<String, List<String>> dataStorage = new LinkedHashMap<>();
        int lineIndex = 0;
        // Initializing 'dataStorage'
        for(String header: headerCount.keySet()) {
            int count = headerCount.get(header);
            dataStorage.put(header, new ArrayList<String>());
            for(int i = 0; i < count; i++) {
                dataStorage.get(header).add(line.get(lineIndex++));
            }
        }
        // Building the returned String
        StringBuilder result = new StringBuilder("{");
        for(String str: dataStorage.keySet()) {
            StringBuilder toAdd = new StringBuilder("." + str + "=");
            if(dataStorage.get(str).size() == 1) {
                toAdd.append(dataStorage.get(str).get(0));
            }
            else {
                toAdd.append("{" + dataStorage.get(str).get(0));
                for(int i = 1; i < dataStorage.get(str).size(); i++) {
                    toAdd.append(", " + dataStorage.get(str).get(i));
                }
                toAdd.append("}");
            }
            result.append(", " + toAdd);
        }
        // Formatting and dealing with fence-post
        return "{" + result.append("}").toString().substring(3);
    }
    
    /**
     * @param header: A List of the headers from the CSV file
     * @return      : A Map that maps each header name to its occurrences
     */
    public static Map<String, Integer> getHeaderCount(List<String> header) {
        Map<String, Integer> headerCount = new LinkedHashMap<>();
        for(String str: header) {
            if(headerCount.containsKey(str)) {
                headerCount.put(str, headerCount.get(str) + 1);
            }
            else {
                headerCount.put(str, 1);
            }
        }
        return headerCount;
    }
}
